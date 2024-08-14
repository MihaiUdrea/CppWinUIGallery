#include "pch.h"
#include "PVSlider.xaml.h"
#if __has_include("PVSlider.g.cpp")
#include "PVSlider.g.cpp"
#include "PVSlider.g.h"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Controls::Primitives;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Media;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t PVSlider::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PVSlider::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    double initialX{ 0 };
    double initialY{ 0 };
    bool dragging{ false };

    void PVSlider::OnThumbDragStarted(IInspectable const& sender, DragStartedEventArgs const& e)
    {
        auto thumb = sender.as<Thumb>();

        // Ensure Thumb has a TranslateTransform in its RenderTransform
        auto transform = thumb.RenderTransform().as<TranslateTransform>();
        if (!transform)
        {
            // Create a new TranslateTransform if none exists
            transform = TranslateTransform();
            thumb.RenderTransform(transform);
        }

        initialX = transform.X();
        initialY = transform.Y();

        dragging = true;

        OutputDebugString(L"Drag started\n");
    }

    void PVSlider::OnThumbDragDelta(IInspectable const& sender, DragDeltaEventArgs const& e)
    {
        if (dragging)
        {
            auto thumb = sender.as<Thumb>();
            auto transform = thumb.RenderTransform().as<TranslateTransform>();

            if (transform)
            {
                // Get the container's size (StackPanel in this case)
                double containerWidth = SliderPanel().ActualWidth();

                // Calculate the new position based on the drag
                double newX = transform.X() + e.HorizontalChange();

                // Define the boundaries
                double leftBoundary = 0.0;
                double rightBoundary = containerWidth - thumb.ActualWidth();

                // Constrain the movement within the boundaries
                newX = std::clamp(newX, leftBoundary, rightBoundary);

                // Update the position of the thumb
                transform.X(newX);

                OutputDebugString(L"Dragging...\n");
            }
        }
    }



    void PVSlider::OnThumbDragCompleted(IInspectable const& sender, DragCompletedEventArgs const& e)
    {
        auto thumb = sender.as<Thumb>();
        auto transform = thumb.RenderTransform().as<TranslateTransform>();

        if (transform)
        {
            // Get the container's size
            double containerWidth = SliderPanel().ActualWidth();

            // Define the two possible snap positions
            double leftPosition = 0.0;
            double rightPosition = containerWidth - thumb.ActualWidth();

            // Snap to the nearest position
            if (transform.X() < (leftPosition + rightPosition) / 2)
            {
                transform.X(leftPosition);
            }
            else
            {
                transform.X(rightPosition);
            }

            OutputDebugString(L"Drag completed, snapped to position\n");
        }

        dragging = false;
    }


  
}
