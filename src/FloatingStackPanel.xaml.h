#pragma once

#include "FloatingStackPanel.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct FloatingStackPanel : FloatingStackPanelT<FloatingStackPanel>
{
    FloatingStackPanel()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);

    void FloatingStackPanel::OnScrollViewerViewChanged(
        IInspectable const &sender, Microsoft::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const &args);
    void ApplyFinalPosition(winrt::Microsoft::UI::Xaml::Controls::ScrollViewer const &scrollViewer, double scale);
    void FloatingStackPanel::AnimateInfobarTransition();
    bool isInInfobarMode = false;
    double lastScale{1.0};
    void SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct FloatingStackPanel : FloatingStackPanelT<FloatingStackPanel, implementation::FloatingStackPanel>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
