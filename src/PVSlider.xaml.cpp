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

        auto transform = thumb.RenderTransform().as<TranslateTransform>();
        if (!transform)
        {
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
                double containerWidth = SliderPanel().ActualWidth();

                double newX = transform.X() + e.HorizontalChange();

                double leftBoundary = 0.0;
                double rightBoundary = containerWidth - thumb.ActualWidth();
                newX = std::clamp(newX, leftBoundary, rightBoundary);

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
            double containerWidth = SliderPanel().ActualWidth();

            double leftPosition = 0.0;
            double rightPosition = containerWidth - thumb.ActualWidth();

            if (transform.X() < (leftPosition + rightPosition) / 2)
            {
                transform.X(leftPosition);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
            }
            else
            {
                transform.X(rightPosition - 3);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
            }



            OutputDebugString(L"Drag completed, snapped to position\n");
        }

        dragging = false;
    }



    void PVSlider::Switch_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto thumb = this->Switch().GetTemplateChild(L"KnobThumb").as<Controls::Primitives::Thumb>();
        auto transform = thumb.RenderTransform().as<TranslateTransform>();

        if (transform) {
            double containerWidth = SliderPanel().ActualWidth();

            double leftPosition = 0.0;
            double rightPosition = containerWidth - thumb.ActualWidth();

            if (transform.X() == leftPosition)
            {
                transform.X(rightPosition - 3);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
            }
            else {
                transform.X(leftPosition);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
            }
        }
    }
}
void winrt::CppWinUIGallery::implementation::PVSlider::SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto textBox = SourceCodeTextBox();
    hstring xamlSourceCode = LR"(
Page.Resources>
        <Style x:Key="Switch" TargetType="ToggleSwitch">
    <Setter Property="Background" Value="{StaticResource ToggleSwitchKnobFillOff}" />
    <Setter Property="Foreground" Value="{StaticResource ToggleSwitchKnobFillOff}" />
            <Setter Property="Template">
                <Setter.Value>
                    <ControlTemplate TargetType="ToggleSwitch" x:Name="ToggleSwitchTemplate">
                        <Grid x:Name="RootGrid" CornerRadius="7" Background="{TemplateBinding Background}">
                            <Grid x:Name="Container">
                                <Grid>
                                    <Thumb x:Name="KnobThumb" Canvas.Left="70"
                           Canvas.Top="20" Margin="0,0,0,0" Width="45" Height="38"
                           CornerRadius="7" HorizontalAlignment="Left"
                           DragStarted="OnThumbDragStarted" 
                           DragDelta="OnThumbDragDelta" 
                           DragCompleted="OnThumbDragCompleted"
                           BorderThickness="1" BorderBrush="#808080">
                                        <Thumb.Background>
                                            <SolidColorBrush Color="#307a7679"/>
                                        </Thumb.Background>

                                        <Thumb.RenderTransform>
                                            <TranslateTransform x:Name="KnobTransform"/>
                                        </Thumb.RenderTransform>
                                    </Thumb>


                                </Grid>
                            </Grid>
                        </Grid>
                    </ControlTemplate>
                </Setter.Value>
            </Setter>
        </Style>


        
        
    </Page.Resources>
    <Grid>
        <StackPanel Margin="0">
            <TextBlock Text="Photo/Video Slider" Margin="50,40" Style="{StaticResource TitleLargeTextBlockStyle}"/>
        </StackPanel>
        <StackPanel x:Name="SliderPanel" Margin="45,120" Orientation="Horizontal" CornerRadius="8" Height="45" BorderBrush="#30292f" BorderThickness="1.5" HorizontalAlignment="Left" VerticalAlignment="Top" >
            <Grid>
                <Rectangle Fill="#211a20" Height="45" Width="90"/>
                <StackPanel VerticalAlignment="Center" Margin="11"  HorizontalAlignment="Left">
                    <SymbolIcon x:Name="CameraIcon" Symbol="Camera"  IsHitTestVisible="True" Foreground="#00ff00"/>
                </StackPanel>
                <StackPanel VerticalAlignment="Center" Margin="0,0,11,0"  HorizontalAlignment="Right">
                    <SymbolIcon x:Name="VideoIcon" Symbol="Video"  IsHitTestVisible="True" Foreground="#80FF0000" />
                </StackPanel>
            </Grid>
        </StackPanel>

        <StackPanel Margin="46,123,0,0">
            <Grid>
            <ToggleSwitch Width="90"  Background="Transparent" x:Name="Switch" Style="{StaticResource Switch}" OffContent="" PointerPressed="Switch_PointerPressed"/>
            </Grid>
        </StackPanel>
    </Grid>

)";
    textBox.Text(xamlSourceCode);
}


void winrt::CppWinUIGallery::implementation::PVSlider::CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto textBox = CppCodeTextBox();
    hstring cppSourceCode = LR"(
 void PVSlider::OnThumbDragStarted(IInspectable const& sender, DragStartedEventArgs const& e)
    {
        auto thumb = sender.as<Thumb>();

        auto transform = thumb.RenderTransform().as<TranslateTransform>();
        if (!transform)
        {
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
                double containerWidth = SliderPanel().ActualWidth();

                double newX = transform.X() + e.HorizontalChange();

                double leftBoundary = 0.0;
                double rightBoundary = containerWidth - thumb.ActualWidth();
                newX = std::clamp(newX, leftBoundary, rightBoundary);

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
            double containerWidth = SliderPanel().ActualWidth();

            double leftPosition = 0.0;
            double rightPosition = containerWidth - thumb.ActualWidth();

            if (transform.X() < (leftPosition + rightPosition) / 2)
            {
                transform.X(leftPosition);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
            }
            else
            {
                transform.X(rightPosition - 3);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
            }



            OutputDebugString(L"Drag completed, snapped to position\n");
        }

        dragging = false;
    }



    void PVSlider::Switch_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto thumb = this->Switch().GetTemplateChild(L"KnobThumb").as<Controls::Primitives::Thumb>();
        auto transform = thumb.RenderTransform().as<TranslateTransform>();

        if (transform) {
            double containerWidth = SliderPanel().ActualWidth();

            double leftPosition = 0.0;
            double rightPosition = containerWidth - thumb.ActualWidth();

            if (transform.X() == leftPosition)
            {
                transform.X(rightPosition - 3);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
            }
            else {
                transform.X(leftPosition);

                CameraIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0xFF, 0x00, 0xFF, 0x00)));
                VideoIcon().Foreground(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(0x80, 0xFF, 0x00, 0x00)));
            }
        }
    }

)";
    textBox.Text(cppSourceCode);

}

