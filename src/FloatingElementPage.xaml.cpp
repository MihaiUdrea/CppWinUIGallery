#include "pch.h"
#include "FloatingElementPage.xaml.h"
#if __has_include("FloatingElementPage.g.cpp")
#include "FloatingElementPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Animation;
using namespace Windows::Foundation;

namespace winrt::CppWinUIGallery::implementation
{
    FloatingElementPage::FloatingElementPage()
    {
        InitializeComponent();

        // Attach event handlers
        auto scrollViewer = FindName(L"mainScrollViewer").try_as<ScrollViewer>();
        if (scrollViewer)
        {
            scrollViewer.ViewChanged({ this, &FloatingElementPage::ScrollViewer_ViewChanged });
        }
        this->Loaded({ this, &FloatingElementPage::Page_Loaded });
    }

    int32_t FloatingElementPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void FloatingElementPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void FloatingElementPage::Page_Loaded(IInspectable const&, RoutedEventArgs const&)
    {
        try
        {
            // Initial check for visibility
            CheckTargetElementVisibility();
        }
        catch (const hresult_error& ex)
        {
            OutputDebugStringW(L"Exception in Page_Loaded: ");
            OutputDebugStringW(ex.message().c_str());
        }
    }

    void FloatingElementPage::ScrollViewer_ViewChanged(IInspectable const&, ScrollViewerViewChangedEventArgs const&)
    {
        try
        {
            CheckTargetElementVisibility();
        }
        catch (const hresult_error& ex)
        {
            OutputDebugStringW(L"Exception in ScrollViewer_ViewChanged: ");
            OutputDebugStringW(ex.message().c_str());
        }
    }

    void FloatingElementPage::CheckTargetElementVisibility()
    {
        try
        {
            auto targetImage = this->targetImage();
            auto scrollViewer = this->mainScrollViewer();
            auto infoBarBorder = this->infoBarBorder();

            if (!targetImage || !scrollViewer || !infoBarBorder)
            {
                OutputDebugStringW(L"One or more elements are null.\n");
                return;
            }

            // Transform the target element's coordinates to the ScrollViewer's coordinate space
            auto transform = targetImage.TransformToVisual(scrollViewer);
            Rect elementRect = transform.TransformBounds(Rect{ 0.0f, 0.0f, static_cast<float>(targetImage.ActualWidth()), static_cast<float>(targetImage.ActualHeight()) });

            // Get the viewport bounds of the ScrollViewer
            Rect viewportRect{ 0.0f, 0.0f, static_cast<float>(scrollViewer.ViewportWidth()), static_cast<float>(scrollViewer.ViewportHeight()) };

            // Get the vertical and horizontal scroll offsets
            float verticalOffset = static_cast<float>(scrollViewer.VerticalOffset());
            float horizontalOffset = static_cast<float>(scrollViewer.HorizontalOffset());

            // Adjust the viewport rectangle by scroll offsets
            viewportRect.X += horizontalOffset;
            viewportRect.Y += verticalOffset;

            // Check if the target element's bounds intersect with the viewport bounds
            bool isInView = (elementRect.X + elementRect.Width > viewportRect.X) &&
                (elementRect.X < viewportRect.X + viewportRect.Width) &&
                (elementRect.Y + elementRect.Height > viewportRect.Y) &&
                (elementRect.Y < viewportRect.Y + viewportRect.Height);

            // Toggle InfoBar visibility based on the target element's visibility
            if (infoBarBorder)
            {
                if (isInView)
                {
                    if (infoBarBorder.Visibility() == Visibility::Visible)
                    {
                        auto slideOut = this->Resources().Lookup(box_value(L"SlideOutAnimation")).try_as<Storyboard>();
                        if (slideOut)
                        {
                            // Create a weak reference to infoBarBorder
                            auto weakInfoBarBorder = winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement>{ infoBarBorder };

                            // Attach a completed handler
                            slideOut.Completed([weakInfoBarBorder](IInspectable const& sender, IInspectable const& args)
                                {
                                    if (auto infoBarBorder = weakInfoBarBorder.get())
                                    {
                                        infoBarBorder.Visibility(Visibility::Collapsed);
                                    }
                                });

                            slideOut.Begin();
                        }
                    }
                }
                else
                {
                    if (infoBarBorder.Visibility() == Visibility::Collapsed)
                    {
                        infoBarBorder.Visibility(Visibility::Visible);
                        auto slideIn = this->Resources().Lookup(box_value(L"SlideInAnimation")).try_as<Storyboard>();
                        if (slideIn)
                        {
                            slideIn.Begin();
                        }
                    }

                    OutputDebugStringW(L"InfoBar is visible.\n");
                }

                OutputDebugStringW(L"InfoBar visibility set.\n");
            }

            // Force a UI update
            this->UpdateLayout();
        }
        catch (const hresult_error& ex)
        {
            OutputDebugStringW(L"Exception in CheckTargetElementVisibility: ");
            OutputDebugStringW(ex.message().c_str());
        }
    }

}
