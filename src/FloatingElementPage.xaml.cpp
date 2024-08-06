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
            auto targetButton = FindName(L"targetButton").try_as<Button>();
            auto infoBarBorder = FindName(L"infoBarBorder").try_as<Border>();
            auto infoBarButton = FindName(L"infoBarButton").try_as<Button>();

            if (!scrollViewer || !targetButton || !infoBarBorder || !infoBarButton)
            {
                return;
            }

            // Helper function to check if a FrameworkElement is nearly out of view
            auto isElementNearlyOutOfView = [&](FrameworkElement const& element) {
                auto transform = element.TransformToVisual(scrollViewer);
                auto position = transform.TransformPoint(Point(0, 0));
                float elementY = static_cast<float>(position.Y);
                float elementHeight = static_cast<float>(element.ActualHeight());

                return (elementY + elementHeight) < 150; // Adjust this threshold as needed
                };

            // Check if the targetButton is nearly out of view
            bool isButtonNearlyOutOfView = isElementNearlyOutOfView(targetButton);

            // Determine the storyboard to use based on visibility
            auto infoBarStoryboardName = isButtonNearlyOutOfView ? L"SlideInAnimation" : L"SlideOutAnimation";
            auto infoBarStoryboard = this->Resources().Lookup(box_value(infoBarStoryboardName)).try_as<Storyboard>();

            if (infoBarStoryboard)
            {
                if (infoBarBorder)
                {
                    if (isButtonNearlyOutOfView)
                    {
                        if (infoBarBorder.Visibility() == Visibility::Collapsed && infoBarStoryboard.GetCurrentState() != ClockState::Active)
                        {
                            // Show the InfoBar
                            infoBarBorder.Visibility(Visibility::Visible);

                            // Prepare and start the connected animation for the targetButton
                            auto connectedAnimationService = ConnectedAnimationService::GetForCurrentView();
                            infoBarStoryboard.Completed([this, connectedAnimationService, targetButton, infoBarButton](IInspectable const&, IInspectable const&)
                                {
                                    // Prepare the connected animation to transition from infoBarButton to targetButton
                                    connectedAnimationService.PrepareToAnimate(L"targetButtonAnimation", targetButton);

                                    auto animation = connectedAnimationService.GetAnimation(L"targetButtonAnimation");
                                    //if (animation)
                                    //{
                                    //    animation.Configuration(DirectConnectedAnimationConfiguration());
                                    //    animation.TryStart(infoBarButton);

                                    //    // Hide the targetButton after the animation starts
                                    //    targetButton.Visibility(Visibility::Collapsed);
                                    //}
                                });

                            infoBarStoryboard.Begin();
                        }
                    }
                    else
                    {
                        if (infoBarBorder.Visibility() == Visibility::Visible && infoBarStoryboard.GetCurrentState() != ClockState::Active)
                        {
                            // Hide the InfoBar first

                            // Prepare and start the reverse connected animation
                            auto connectedAnimationService = ConnectedAnimationService::GetForCurrentView();
                            connectedAnimationService.PrepareToAnimate(L"infoBarButtonAnimation", infoBarButton);

                            auto reverseAnimation = connectedAnimationService.GetAnimation(L"infoBarButtonAnimation");
                            if (reverseAnimation)
                            {
                                reverseAnimation.Configuration(DirectConnectedAnimationConfiguration());

                                reverseAnimation.Completed([this, targetButton](IInspectable const&, IInspectable const&)
                                    {
                                        // Make sure to show the targetButton after the reverse animation completes
                                        targetButton.Visibility(Visibility::Visible);
                                    });

                                reverseAnimation.TryStart(targetButton);
                            }

                            // Start the storyboard after hiding the InfoBar
                            infoBarStoryboard.Begin();
                        }
                    }
                }
            }

            // Force a UI update
            this->UpdateLayout();
        }
        catch (const hresult_error& ex)
        {
            // Handle exception
            UNREFERENCED_PARAMETER(ex); // Remove unused variable warning
        }
    }



















    void FloatingElementPage::ShowSourceCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();
        auto cppTextBox = CppCodeTextBox();
        auto cppButton = ShowCppButton(); // Ensure ShowCppButton is correctly named and initialized

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
           /* if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }*/

            // Show XAML source code
            hstring xamlSourceCode = LR"(
<Page.Resources>
    <!-- Slide in animation -->
    <Storyboard x:Key="SlideInAnimation">
        <DoubleAnimation 
            Storyboard.TargetName="infoBarBorder"
            Storyboard.TargetProperty="(UIElement.RenderTransform).(TranslateTransform.Y)&quot"
                From = "-100" To = "0" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "infoBarBorder"
                Storyboard.TargetProperty = "(UIElement.Opacity)&quot"
                From = "0" To = "1" Duration = "0:0:0.4"
                EnableDependentAnimation = "True" / >
                < / Storyboard>

                <!--Slide out animation-->
                <Storyboard x : Key = "SlideOutAnimation">
                <DoubleAnimation
                Completed = "DoubleAnimation_Completed"
                Storyboard.TargetName = "infoBarBorder"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(TranslateTransform.Y)&quot"
                From = "0" To = "-100" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "infoBarBorder"
                Storyboard.TargetProperty = "(UIElement.Opacity)&quot"
                From = "1" To = "0" Duration = "0:0:0.4"
                EnableDependentAnimation = "True" / >
                < / Storyboard>

                <Storyboard x : Key = "MinimizeElements">
                <DoubleAnimation
                Storyboard.TargetName = "targetImage"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetImage"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetTextBlock"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetTextBlock"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetButton"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetButton"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "0.5" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetStackPanel"
                Storyboard.TargetProperty = "Opacity"
                To = "0" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                < / Storyboard>

                <Storyboard x : Key = "RestoreElements">
                <DoubleAnimation
                Storyboard.TargetName = "targetImage"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetImage"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetTextBlock"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetTextBlock"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetButton"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleX)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetButton"
                Storyboard.TargetProperty = "(UIElement.RenderTransform).(CompositeTransform.ScaleY)&quot"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                <DoubleAnimation
                Storyboard.TargetName = "targetStackPanel"
                Storyboard.TargetProperty = "Opacity"
                To = "1" Duration = "0:0:0.3"
                EnableDependentAnimation = "True" / >
                < / Storyboard>
                < / Page.Resources>

                <Grid>
                <ScrollViewer x : Name = "mainScrollViewer" ViewChanged = "ScrollViewer_ViewChanged">
                <StackPanel>
                <StackPanel>
                <TextBlock Text = "Animated Floating InfoBar - Scroll down!" HorizontalAlignment = "Center" Style = "{StaticResource TitleTextBlockStyle}" Margin = "0,40" / >
                < / StackPanel>
                <StackPanel x : Name = "targetStackPanel" Background = "#80000000" Width = "900" CornerRadius = "60" HorizontalAlignment = "Center" Margin = "36" Height = "360" Opacity = "1">
                <Image x : Name = "targetImage" Source = "ms-appx:///Assets/ai_logo_img.png" VerticalAlignment = "Top" AutomationProperties.Name = "AdvancedInstaller" HorizontalAlignment = "Left" Width = "200" Height = "200" Margin = "36,80">
                <Image.RenderTransform>
                <CompositeTransform / >
                < / Image.RenderTransform>
                < / Image>
                <TextBlock x : Name = "targetTextBlock" Text = "Windows Installer Packaging Tool for Developers, ISVs &amp; Enterprises" Style = "{StaticResource TitleTextBlockStyle}" HorizontalAlignment = "Left" VerticalAlignment = "Top" Width = "400" Margin = "260,-290">
                <TextBlock.RenderTransform>
                <CompositeTransform / >
                < / TextBlock.RenderTransform>
                < / TextBlock>
                <Button x : Name = "targetButton" Style = "{StaticResource AccentButtonStyle}" Content = "Get" Width = "195" HorizontalAlignment = "Left" Margin = "670,-530,0,0">
                <Button.RenderTransform>
                <CompositeTransform / >
                < / Button.RenderTransform>
                < / Button>
                < / StackPanel>
                < / ScrolLViewer>
                < / Grid>
)";
            textBox.Text(xamlSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide XAML"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show XAML"));
        }
    }

    void FloatingElementPage::ShowCppCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowCppButton(); // Make sure the button is named correctly
        auto textBox = CppCodeTextBox();
        auto xamlTextBox = SourceCodeTextBox();
        auto xamlButton = ShowHideButton(); // Ensure ShowHideButton is correctly named and initialized

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide XAML code if visible
           /* if (xamlTextBox.Visibility() == Visibility::Visible)
            {
                xamlTextBox.Visibility(Visibility::Collapsed);
                xamlButton.Content(box_value(L"Show XAML"));
            }*/

            // Show C++ source code
            hstring cppSourceCode = LR"(
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
)";
            textBox.Text(cppSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide C++"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show C++"));
        }
    }



    void FloatingElementPage::DoubleAnimation_Completed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
    {
        auto infoBarBorder = FindName(L"infoBarBorder").try_as<Border>();

        infoBarBorder.Visibility(Visibility::Collapsed);

    }






}


