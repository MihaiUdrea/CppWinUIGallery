#include "pch.h"
#include "FloatingStackPanel.xaml.h"
#if __has_include("FloatingStackPanel.g.cpp")
#include "FloatingStackPanel.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;

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
        // Cast sender to ScrollViewer
        auto scrollViewer = sender.as<ScrollViewer>();
        double offsetY = scrollViewer.VerticalOffset();

        // Define thresholds and minimum scale
        const double startScalingOffset = 200; // The point where scaling starts
        const double stopScalingOffset = 600;  // The point where scaling stops and the panel sticks to the top
        const double minScale = 0.1;

        // Calculate scale based on scroll offset
        double scale = 1.0;
        if (offsetY > startScalingOffset)
        {
            double scaleFactor = 1.0 - (offsetY - startScalingOffset) / (stopScalingOffset - startScalingOffset);
            scale = scaleFactor < minScale ? minScale : scaleFactor;
        }

        // Calculate translation to stick the panel to the top of the viewport
        double translationY = 0;
        if (offsetY > stopScalingOffset)
        {
            translationY = -(offsetY - stopScalingOffset) * (1.0 - minScale);
        }

        // Retrieve and update transforms for the StackPanel and its children
        auto stackPanelTransform = targetStackPanel().RenderTransform().as<CompositeTransform>();
        if (!stackPanelTransform)
        {
            stackPanelTransform = CompositeTransform();
            targetStackPanel().RenderTransform(stackPanelTransform);
        }

        // Apply scaling and translation only once when needed
        if (offsetY > startScalingOffset && !isScaledDown)
        {
            stackPanelTransform.ScaleX(scale);
            stackPanelTransform.ScaleY(scale);
            stackPanelTransform.TranslateY(translationY);
            isScaledDown = true; // Mark scaling as applied
        }
        else if (offsetY <= startScalingOffset && isScaledDown)
        {
            stackPanelTransform.ScaleX(1.0);
            stackPanelTransform.ScaleY(1.0);
            stackPanelTransform.TranslateY(0);
            isScaledDown = false; // Mark scaling as reset
        }

        auto imageTransform = targetImage().RenderTransform().as<CompositeTransform>();
        if (!imageTransform)
        {
            imageTransform = CompositeTransform();
            targetImage().RenderTransform(imageTransform);
        }

        // Update image transform only if the scale or translation has changed
        if (offsetY > startScalingOffset && !isScaledDown)
        {
            imageTransform.ScaleX(scale);
            imageTransform.ScaleY(scale);
            imageTransform.TranslateY(translationY);
        }
        else if (offsetY <= startScalingOffset && isScaledDown)
        {
            imageTransform.ScaleX(1.0);
            imageTransform.ScaleY(1.0);
            imageTransform.TranslateY(0);
        }

        auto textTransform = targetTextBlock().RenderTransform().as<CompositeTransform>();
        if (!textTransform)
        {
            textTransform = CompositeTransform();
            targetTextBlock().RenderTransform(textTransform);
        }

        // Update text transform only if the scale or translation has changed
        if (offsetY > startScalingOffset && !isScaledDown)
        {
            textTransform.ScaleX(scale);
            textTransform.ScaleY(scale);
            textTransform.TranslateY(translationY);
        }
        else if (offsetY <= startScalingOffset && isScaledDown)
        {
            textTransform.ScaleX(1.0);
            textTransform.ScaleY(1.0);
            textTransform.TranslateY(0);
        }

        auto buttonTransform = targetButton().RenderTransform().as<CompositeTransform>();
        if (!buttonTransform)
        {
            buttonTransform = CompositeTransform();
            targetButton().RenderTransform(buttonTransform);
        }

        // Update button transform only if the scale or translation has changed
        if (offsetY > startScalingOffset && !isScaledDown)
        {
            buttonTransform.ScaleX(scale);
            buttonTransform.ScaleY(scale);
            buttonTransform.TranslateY(translationY);
        }
        else if (offsetY <= startScalingOffset && isScaledDown)
        {
            buttonTransform.ScaleX(1.0);
            buttonTransform.ScaleY(1.0);
            buttonTransform.TranslateY(0);
        }

        // Change background color based on scale
        auto stackPanelBackground = targetStackPanel().Background().as<SolidColorBrush>();
        Windows::UI::Color newColor = (scale < 1.0) ? Windows::UI::Colors::Black() : Windows::UI::ColorHelper::FromArgb(0x80, 0x00, 0x00, 0x00);

        if (!stackPanelBackground || stackPanelBackground.Color() != newColor)
        {
            targetStackPanel().Background(SolidColorBrush(newColor));
        }
    }
}
