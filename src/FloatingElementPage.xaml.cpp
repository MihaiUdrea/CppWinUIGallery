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
           /* OutputDebugStringW(L"Exception in Page_Loaded: ");
            OutputDebugStringW(ex.message().c_str());*/
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
          /*  OutputDebugStringW(L"Exception in ScrollViewer_ViewChanged: ");
            OutputDebugStringW(ex.message().c_str());*/
        }
    }

    void FloatingElementPage::CheckTargetElementVisibility()
    {
        try
        {
            // Retrieve the UI elements
            auto scrollViewer = FindName(L"mainScrollViewer").try_as<ScrollViewer>();
            auto targetImage = FindName(L"targetImage").try_as<Image>();
            auto infoBarBorder = FindName(L"infoBarBorder").try_as<Border>();

            if (!scrollViewer || !targetImage || !infoBarBorder)
            {
                return;
            }

            // Get viewport dimensions
            float viewportWidth = static_cast<float>(scrollViewer.ViewportWidth());
            float viewportHeight = static_cast<float>(scrollViewer.ViewportHeight());

            // Transform target image to scroll viewer coordinates
            auto targetImageTransform = targetImage.TransformToVisual(scrollViewer);
            auto targetImagePosition = targetImageTransform.TransformPoint(Point(0, 0));

            float targetImageX = static_cast<float>(targetImagePosition.X);
            float targetImageY = static_cast<float>(targetImagePosition.Y);
            float targetImageWidth = static_cast<float>(targetImage.ActualWidth());
            float targetImageHeight = static_cast<float>(targetImage.ActualHeight());

            Rect targetImageRect(targetImageX, targetImageY, targetImageWidth, targetImageHeight);

            // Determine if the target image is in view
            float targetImageTop = targetImageRect.Y;
            float targetImageBottom = targetImageRect.Y + targetImageRect.Height;
            float targetImageLeft = targetImageRect.X;
            float targetImageRight = targetImageRect.X + targetImageRect.Width;

            bool isInView = (targetImageBottom > 0 &&
                targetImageTop < viewportHeight) &&
                (targetImageRight > 0 &&
                    targetImageLeft < viewportWidth);

            // Determine the storyboard to use based on visibility
            auto storyboardName = isInView ? L"SlideOutAnimation" : L"SlideInAnimation";
            auto storyboard = this->Resources().Lookup(box_value(storyboardName)).try_as<Storyboard>();

            if (!storyboard)
            {
                return;
            }

            if (infoBarBorder)
            {
                if (isInView)
                {
                    // Image is in view; InfoBar should slide out and become collapsed
                    if (infoBarBorder.Visibility() == Visibility::Visible && storyboard.GetCurrentState() != ClockState::Active)
                    {
                        // Slide out animation
                        auto weakInfoBarBorder = winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement>{ infoBarBorder };

                        storyboard.Completed([weakInfoBarBorder](IInspectable const&, IInspectable const&)
                            {
                                if (auto strongInfoBarBorder = weakInfoBarBorder.get())
                                {
                                    strongInfoBarBorder.Visibility(Visibility::Collapsed);
                                }
                            });

                        storyboard.Begin();
                    }
                }
                else
                {
                    // Image is not in view; InfoBar should slide in and become visible
                    if (infoBarBorder.Visibility() == Visibility::Collapsed && storyboard.GetCurrentState() != ClockState::Active)
                    {
                        infoBarBorder.Visibility(Visibility::Visible);
                        storyboard.Begin();
                    }
                }
            }

            // Force a UI update
            this->UpdateLayout();
        }
        catch (const hresult_error& ex)
        {
            // Handle exception
            // For example: OutputDebugStringW(ex.message().c_str());
        }
    }




    void FloatingElementPage::DoubleAnimation_Completed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
    {
        auto infoBarBorder = FindName(L"infoBarBorder").try_as<Border>();

        infoBarBorder.Visibility(Visibility::Collapsed);

    }






}



