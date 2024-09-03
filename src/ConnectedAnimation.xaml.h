#pragma once

#include "ConnectedAnimation.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct ConnectedAnimation : ConnectedAnimationT<ConnectedAnimation>
{
    ConnectedAnimation()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);

    void OnPointerExit(winrt::Windows::Foundation::IInspectable const &sender,
                       winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const &e);
    void OnPointerEnter(winrt::Windows::Foundation::IInspectable const &sender,
                        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const &e);
    bool m_hovered = false;
    bool m_pointerInside = false; // Track whether the pointer is inside the element
    bool m_animationInProgress = false;
    bool m_autoReverseRequested = false; // New flag to track auto-reverse requests
    bool m_sizedDown = false;
    winrt::fire_and_forget LoadFileContent(hstring const &filePath,
                                           winrt::Microsoft::UI::Xaml::Controls::TextBox textBox);
    std::wstring GetCurrentWorkingDirectory();
    void SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct ConnectedAnimation : ConnectedAnimationT<ConnectedAnimation, implementation::ConnectedAnimation>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
