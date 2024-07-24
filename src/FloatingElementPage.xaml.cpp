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
            auto scrollViewer = FindName(L"mainScrollViewer").as<ScrollViewer>();
            auto targetImage = FindName(L"targetImage").try_as<FrameworkElement>();
            auto targetTextBlock = FindName(L"targetTextBlock").try_as<FrameworkElement>();
            auto targetButton = FindName(L"targetButton").try_as<FrameworkElement>();
            auto infoBarBorder = FindName(L"infoBarBorder").try_as<Border>();

            if (!scrollViewer || !targetImage || !targetTextBlock || !targetButton || !infoBarBorder)
            {
                return;
            }

            // Get viewport dimensions
            float viewportWidth = static_cast<float>(scrollViewer.ViewportWidth());
            float viewportHeight = static_cast<float>(scrollViewer.ViewportHeight());

            // Helper function to check if a FrameworkElement is nearly out of view
            auto isElementNearlyOutOfView = [&](FrameworkElement const& element) {
                auto transform = element.TransformToVisual(scrollViewer);
                auto position = transform.TransformPoint(Point(0, 0));
                float elementY = static_cast<float>(position.Y);
                float elementHeight = static_cast<float>(element.ActualHeight());

                return (elementY + elementHeight) < 150; // Adjust this threshold as needed
                };

            // Check if any of the target elements are nearly out of view
            bool isAnyElementNearlyOutOfView = isElementNearlyOutOfView(targetImage) || isElementNearlyOutOfView(targetTextBlock) || isElementNearlyOutOfView(targetButton);

            // Determine the storyboard to use based on visibility
            auto storyboardName = isAnyElementNearlyOutOfView ? L"MinimizeElements" : L"RestoreElements";
            auto storyboard = this->Resources().Lookup(box_value(storyboardName)).try_as<Storyboard>();

            if (!storyboard)
            {
                return;
            }

            storyboard.Begin();

            // Handle InfoBar visibility
            auto infoBarStoryboardName = isAnyElementNearlyOutOfView ? L"SlideInAnimation" : L"SlideOutAnimation";
            auto infoBarStoryboard = this->Resources().Lookup(box_value(infoBarStoryboardName)).try_as<Storyboard>();

            if (!infoBarStoryboard)
            {
                return;
            }

            if (infoBarBorder)
            {
                if (isAnyElementNearlyOutOfView)
                {
                    if (infoBarBorder.Visibility() == Visibility::Collapsed && infoBarStoryboard.GetCurrentState() != ClockState::Active)
                    {
                        infoBarBorder.Visibility(Visibility::Visible);
                        infoBarStoryboard.Begin();
                    }
                }
                else
                {
                    if (infoBarBorder.Visibility() == Visibility::Visible && infoBarStoryboard.GetCurrentState() != ClockState::Active)
                    {
                        auto weakInfoBarBorder = winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement>{ infoBarBorder };

                        infoBarStoryboard.Completed([weakInfoBarBorder](IInspectable const&, IInspectable const&)
                            {
                                if (auto strongInfoBarBorder = weakInfoBarBorder.get())
                                {
                                    strongInfoBarBorder.Visibility(Visibility::Collapsed);
                                }
                            });

                        infoBarStoryboard.Begin();
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



