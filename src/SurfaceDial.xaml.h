#pragma once

#include "SurfaceDial.g.h"
#include "winrt/Windows.System.Threading.h"
#include "winrt/Windows.UI.Xaml.Controls.h"
#include "winrt/Windows.UI.Xaml.Input.h"
#include "winrt/Windows.UI.Xaml.Shapes.h"
#include "winrt/Windows.UI.Xaml.Media.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.UI.Xaml.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SurfaceDial : SurfaceDialT<SurfaceDial>
    {
        SurfaceDial()
        {
            
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void hoverSection_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void hoverSection_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        winrt::Microsoft::UI::Xaml::DispatcherTimer m_timer{ nullptr };
        winrt::Microsoft::UI::Xaml::Shapes::Path m_previousMenuSection{ nullptr };
        void UpdateApplicationName(hstring const& sectionName);
        int m_currentIndex{ 0 };

      
        winrt::Microsoft::UI::Xaml::Shapes::Path m_currentHoverSection{ nullptr };
     
        void hoverSection_Tapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::TappedRoutedEventArgs const& e);
        void winrt::CppWinUIGallery::implementation::SurfaceDial::ClickAnimation_Completed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
        void WindowsPage_PointerWheelChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        bool m_isEnterKeyPressed = false;  
        void winrt::CppWinUIGallery::implementation::SurfaceDial::PageKeyDown(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void StackPanel_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        bool ignorePointerEvents = false;

    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SurfaceDial : SurfaceDialT<SurfaceDial, implementation::SurfaceDial>
    {
    };
}
