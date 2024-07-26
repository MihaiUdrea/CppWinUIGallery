#include "pch.h"
#include "FloatingStackPanel.xaml.h"
#if __has_include("FloatingStackPanel.g.cpp")
#include "FloatingStackPanel.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Animation;

namespace winrt::CppWinUIGallery::implementation
{
    int32_t FloatingStackPanel::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void FloatingStackPanel::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    bool isScaledDown = false; // Flag to track whether scaling has been applied

    void FloatingStackPanel::OnScrollViewerViewChanged(IInspectable const& sender, ScrollViewerViewChangedEventArgs const& args)
    {
        auto scrollViewer = sender.as<ScrollViewer>();
        double offsetY = scrollViewer.VerticalOffset();

        // Define thresholds and scale factors
        const double startScalingOffset = 350; // The point where scaling starts
        const double stopScalingOffset = 900;  // The point where scaling stops and the panel sticks to the top
        const double infobarScale = 0.55; // Scale factor for the infobar size
        const double infobarTopOffset = 200; // Offset from the top of the screen when in infobar mode
        const double infobarWidth = 900; // Width of the infobar when scaled (unchanged)

        // Calculate scale and translation based on scroll offset
        double scale = 1.0;
        double translationY = 0;
        double horizontalOffset = 0;

        if (offsetY > startScalingOffset)
        {
            scale = infobarScale;
            translationY = offsetY - startScalingOffset + infobarTopOffset;
            horizontalOffset = 0;
        }
        else
        {
            scale = 1.0;
            translationY = 0;
            horizontalOffset = 0;
        }

        // Retrieve the Storyboard from XAML
        auto scaleStoryboard = this->FindName(L"ScaleStoryboard").as<Storyboard>();
        if (scaleStoryboard)
        {
            // Set the target properties for animation
            auto scaleXAnimation = scaleStoryboard.Children().GetAt(0).as<DoubleAnimation>();
            auto scaleYAnimation = scaleStoryboard.Children().GetAt(1).as<DoubleAnimation>();
            auto translateXAnimation = scaleStoryboard.Children().GetAt(2).as<DoubleAnimation>();
            auto translateYAnimation = scaleStoryboard.Children().GetAt(3).as<DoubleAnimation>();

            if (scaleXAnimation)
            {
                scaleXAnimation.To(scale);
            }
            if (scaleYAnimation)
            {
                scaleYAnimation.To(scale);
            }
            if (translateXAnimation)
            {
                translateXAnimation.To(horizontalOffset);
            }
            if (translateYAnimation)
            {
                translateYAnimation.To(translationY);
            }

            // Start the storyboard
            scaleStoryboard.Begin();
        }

        // Maintain the fixed width of the StackPanel
        targetStackPanel().Width(infobarWidth);

        // Change background color based on scale
        auto stackPanelBackground = targetStackPanel().Background().as<SolidColorBrush>();
        Windows::UI::Color newColor = (scale < 1.0) ? Windows::UI::Colors::Black() : Windows::UI::ColorHelper::FromArgb(0x80, 0x00, 0x00, 0x00);

        if (!stackPanelBackground || stackPanelBackground.Color() != newColor)
        {
            targetStackPanel().Background(SolidColorBrush(newColor));
        }
    }
}