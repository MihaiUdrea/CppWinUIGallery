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

        if (offsetY > startScalingOffset)
        {
            scale = infobarScale;
            translationY = offsetY - startScalingOffset + infobarTopOffset;
        }
        else
        {
            scale = 1.0;
            translationY = 0;
        }

        // Apply transformations directly
        auto transform = targetStackPanel().RenderTransform().as<CompositeTransform>();
        transform.TranslateY(translationY);

        // Maintain the fixed width of the StackPanel
        targetStackPanel().Width(infobarWidth);

        // Change background color based on scale
        auto stackPanelBackground = targetStackPanel().Background().as<SolidColorBrush>();
        Windows::UI::Color newColor = (scale < 1.0) ? Windows::UI::Colors::Black() : Windows::UI::ColorHelper::FromArgb(0x80, 0x00, 0x00, 0x00);

        if (!stackPanelBackground || stackPanelBackground.Color() != newColor)
        {
            targetStackPanel().Background(SolidColorBrush(newColor));
        }

        // Update text wrapping based on scale
        auto targetTextBlock = targetStackPanel().FindName(L"targetTextBlock").as<TextBlock>();


        // Trigger animations when transitioning
        if (scale < 1.0 && !isScaledDown)
        {
            isScaledDown = true;
            ScaleDownStoryboard().Begin();
        }
        else if (scale == 1.0 && isScaledDown)
        {
            isScaledDown = false;
            ScaleUpStoryboard().Begin();
        }
    }
    void FloatingStackPanel::ShowSourceCode_Click(
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
    <Storyboard x:Name="ScaleUpStoryboard">
        <DoubleAnimation
            Storyboard.TargetName="stackPanelTransform"
            Storyboard.TargetProperty="ScaleX"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="stackPanelTransform"
            Storyboard.TargetProperty="ScaleY"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="imageTransform"
            Storyboard.TargetProperty="ScaleX"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="imageTransform"
            Storyboard.TargetProperty="ScaleY"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="buttonTransform"
            Storyboard.TargetProperty="ScaleX"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
             Storyboard.TargetName="buttonTransform"
             Storyboard.TargetProperty="ScaleY"
             To="1.0"
             Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="textTransform"
            Storyboard.TargetProperty="ScaleX"
            To="1.0"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="textTransform"
            Storyboard.TargetProperty="ScaleY"
            To="1.0"
            Duration="0:0:0.3" />
    </Storyboard>
    <Storyboard x:Name="ScaleDownStoryboard">
        <DoubleAnimation
            Storyboard.TargetName="stackPanelTransform"
            Storyboard.TargetProperty="ScaleX"
            To="0.65"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="buttonTransform"
            Storyboard.TargetProperty="ScaleY"
            To="3.60"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="buttonTransform"
            Storyboard.TargetProperty="ScaleX"
            To="1.25"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="imageTransform"
            Storyboard.TargetProperty="ScaleX"
            To="0.65"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="imageTransform"
            Storyboard.TargetProperty="ScaleY"
            To="1.55"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="textTransform"
            Storyboard.TargetProperty="ScaleX"
            To="0.9"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="textTransform"
            Storyboard.TargetProperty="ScaleY"
            To="2.5"
            Duration="0:0:0.3" />
        <DoubleAnimation
            Storyboard.TargetName="stackPanelTransform"
            Storyboard.TargetProperty="ScaleY"
            To="0.25"
            Duration="0:0:0.3" />
    </Storyboard>
</Page.Resources>

<Grid x:Name="PageRoot">
    <ScrollViewer x:Name="mainScrollViewer" VerticalScrollBarVisibility="Auto" ViewChanged="OnScrollViewerViewChanged">
        <StackPanel>
            <StackPanel>
                <TextBlock Text="Animated Floating InfoBar - Scroll down!" HorizontalAlignment="Center" Style="{StaticResource TitleTextBlockStyle}" Margin="0,40"/>
            </StackPanel>
            <StackPanel x:Name="targetStackPanel" Background="#80000000" Width="900" CornerRadius="60" HorizontalAlignment="Center" Margin="36,0,36,0" Height="360" Opacity="1">
                <StackPanel.RenderTransform>
                    <CompositeTransform x:Name="stackPanelTransform" CenterX="450" CenterY="180"/>
                </StackPanel.RenderTransform>
                <Image x:Name="targetImage" Source="ms-appx:///Assets/ai_logo_img.png" VerticalAlignment="Top" AutomationProperties.Name="AdvancedInstaller" HorizontalAlignment="Left" Width="200" Height="200" Margin="36,80">
                    <Image.RenderTransform>
                        <CompositeTransform x:Name="imageTransform" CenterX="100" CenterY="100"/>
                    </Image.RenderTransform>
                </Image>
                <Button x:Name="targetButton" Style="{StaticResource AccentButtonStyle}" Content="Get" Width="195" HorizontalAlignment="Left" VerticalAlignment="Center" Margin="655,-590,0,0">
                    <Button.RenderTransform>
                        <CompositeTransform x:Name="buttonTransform" CenterX="97.5" CenterY="-16.5"/>
                    </Button.RenderTransform>
                </Button>
                <TextBlock x:Name="targetTextBlock" Text="Windows Installer Packaging Tool for Developers, ISVs &amp; Enterprises" Style="{StaticResource TitleTextBlockStyle }" HorizontalAlignment="Left" VerticalAlignment="Top" Width="400" Margin="250,-320">
                    <TextBlock.RenderTransform>
                        <CompositeTransform x:Name="textTransform"/>
                    </TextBlock.RenderTransform>
                </TextBlock>

            </StackPanel>
	</StackPanel>
    </ScrollViewer>
</Grid>
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

    void FloatingStackPanel::ShowCppCode_Click(
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

        if (offsetY > startScalingOffset)
        {
            scale = infobarScale;
            translationY = offsetY - startScalingOffset + infobarTopOffset;
        }
        else
        {
            scale = 1.0;
            translationY = 0;
        }

        // Apply transformations directly
        auto transform = targetStackPanel().RenderTransform().as<CompositeTransform>();
        transform.TranslateY(translationY);

        // Maintain the fixed width of the StackPanel
        targetStackPanel().Width(infobarWidth);

        // Change background color based on scale
        auto stackPanelBackground = targetStackPanel().Background().as<SolidColorBrush>();
        Windows::UI::Color newColor = (scale < 1.0) ? Windows::UI::Colors::Black() : Windows::UI::ColorHelper::FromArgb(0x80, 0x00, 0x00, 0x00);

        if (!stackPanelBackground || stackPanelBackground.Color() != newColor)
        {
            targetStackPanel().Background(SolidColorBrush(newColor));
        }

        // Update text wrapping based on scale
        auto targetTextBlock = targetStackPanel().FindName(L"targetTextBlock").as<TextBlock>();


        // Trigger animations when transitioning
        if (scale < 1.0 && !isScaledDown)
        {
            isScaledDown = true;
            ScaleDownStoryboard().Begin();
        }
        else if (scale == 1.0 && isScaledDown)
        {
            isScaledDown = false;
            ScaleUpStoryboard().Begin();
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
}

