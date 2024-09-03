#pragma once

#include "PVSlider.g.h"
#include "winrt/Microsoft.UI.Xaml.Controls.h"
#include "winrt/Microsoft.UI.Xaml.Input.h"
#include "winrt/Microsoft.UI.Xaml.h"

namespace winrt::CppWinUIGallery::implementation
{
struct PVSlider : PVSliderT<PVSlider>
{
    PVSlider()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);
    void OnThumbDragStarted(winrt::Windows::Foundation::IInspectable const &sender,
                            winrt::Microsoft::UI::Xaml::Controls::Primitives::DragStartedEventArgs const &e);
    void OnThumbDragDelta(winrt::Windows::Foundation::IInspectable const &sender,
                          winrt::Microsoft::UI::Xaml::Controls::Primitives::DragDeltaEventArgs const &e);
    void OnThumbDragCompleted(winrt::Windows::Foundation::IInspectable const &sender,
                              winrt::Microsoft::UI::Xaml::Controls::Primitives::DragCompletedEventArgs const &e);

    double initialX{0};
    double initialY{0};
    bool dragging{false};

    void Switch_PointerPressed(winrt::Windows::Foundation::IInspectable const &sender,
                               winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const &e);
    void SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct PVSlider : PVSliderT<PVSlider, implementation::PVSlider>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
