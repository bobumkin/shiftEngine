#include "App.h"
#include "drawable/Box.h"
#include "drawable/Cylinder.h"
#include "drawable/Pyramid.h"
#include "drawable/SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "CustomMath.h"
#include "bindable/Surface.h"
#include "drawable/GDIPlusManager.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd(1600, 900, "Shift engine"),
	light(wnd.Gfx())
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			const DirectX::XMFLOAT3 mat = { cdist(rng),cdist(rng),cdist(rng) };

			switch (sdist(rng))
			{
			case 0:
				return std::make_unique<Box>(
					gfx,rng,adist,ddist,
					odist,rdist,bdist,mat
				);
			case 1:
				return std::make_unique<Cylinder>(
					gfx, rng, adist, ddist, odist,
					rdist, bdist, tdist
				);
			case 2:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist, odist, 
					rdist, tdist
				);
			case 3:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist, 
					odist, rdist
				);
			default:
				assert(false && "impossible drawable option in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> sdist{ 0, 3 };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f,1.0f };
		std::uniform_int_distribution<int> tdist{ 3,30 };
	};

	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ wnd.Gfx() });

	for (auto& pd : drawables) {
		if (auto pb = dynamic_cast<Box*>(pd.get())) {
			boxes.push_back(pb);
		}
	}

	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
}

int App::Go()
{
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}
		DoFrame();
	}
}

App::~App()
{}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());

	for (auto& d : drawables) {
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}
	light.Draw(wnd.Gfx());

	SpawnSimulationWindow();
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	SpawnBoxWindowManagerWindow();
	SpawnBoxWindows();

	wnd.Gfx().EndFrame();
}

void App::SpawnSimulationWindow() noexcept
{
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 4.0f, "%.4f", 3.2f);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
	}
	ImGui::End();
}

void App::SpawnBoxWindowManagerWindow() noexcept
{
	if (ImGui::Begin("Boxes")) {
		using namespace std::string_literals;
		const auto preview = comboBoxIndex ? std::to_string(*comboBoxIndex) : "Choose a box..."s;
		if (ImGui::BeginCombo("Box Number", preview.c_str())) {
			for (int i = 0; i < boxes.size(); i++)
			{
				const bool selected = *comboBoxIndex == i;
				if (ImGui::Selectable(std::to_string(i).c_str(), selected)) {
					comboBoxIndex = i;
				}
				if (selected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Spawn Control Window") && comboBoxIndex) {
			boxControlIds.insert(*comboBoxIndex);
			comboBoxIndex.reset();
		}
	}
	ImGui::End();
}

void App::SpawnBoxWindows() noexcept
{
	for (auto i = boxControlIds.begin(); i != boxControlIds.end(); ) {
		if (!boxes[*i]->SpawnControlWindow(*i, wnd.Gfx())) {
			i = boxControlIds.erase(i);
		}
		else {
			i++;
		}
	}
}