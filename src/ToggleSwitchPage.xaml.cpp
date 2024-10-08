#include "pch.h"

#include "ToggleSwitchPage.xaml.h"
#if __has_include("ToggleSwitchPage.g.cpp")
#include "ToggleSwitchPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

namespace winrt::CppWinUIGallery::implementation
{
int32_t ToggleSwitchPage::MyProperty()
{
    throw hresult_not_implemented();
}

void ToggleSwitchPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void ToggleSwitchPage::SubscriptionToggleSwitch_Toggled(winrt::Windows::Foundation::IInspectable const &sender,
                                                        winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto toggleSwitch = SubscriptionToggleSwitch();
    auto subscriptionBorder = SubscriptionText().Parent().as<Border>();
    auto perpetualBorder = PerpetualText().Parent().as<Border>();

    SolidColorBrush greenBrush{Colors::Green()};
    SolidColorBrush blueBrush{Colors::Blue()};
    SolidColorBrush whiteBrush{Colors::White()};
    auto customColor = Windows::UI::ColorHelper::FromArgb(58, 56, 245, 212);
    SolidColorBrush customBrush{customColor};

    if (toggleSwitch.IsOn())
    {
        subscriptionBorder.Background(customBrush);
        perpetualBorder.Background(blueBrush);
        perpetualBorder.Child().as<TextBlock>().Foreground(whiteBrush);
    }
    else
    {
        subscriptionBorder.Background(greenBrush);
        subscriptionBorder.Child().as<TextBlock>().Foreground(whiteBrush);
        perpetualBorder.Background(customBrush);
    }
}

} // namespace winrt::CppWinUIGallery::implementation

void winrt::CppWinUIGallery::implementation::ToggleSwitchPage::SourceCodeTextBox_Loaded(
    winrt::Windows::Foundation::IInspectable const &sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{

    auto textBox = SourceCodeTextBox();

    hstring xamlSourceCode = LR"(
<TextBlock Text="ToggleSwitch" Style="{StaticResource TitleLargeTextBlockStyle}" Margin="50,40"/>

<!-- SUBSCRIPTION BLOCK -->
<Border x:Name="SubscriptionBorder" Background="Green" HorizontalAlignment="Left" VerticalAlignment="Top" Margin="40,116,140,0" CornerRadius="20" Width="210" Canvas.ZIndex="0">
    <TextBlock x:Name="SubscriptionText" Text="Subscription" Foreground="White" HorizontalAlignment="Center" VerticalAlignment="Center" Margin="10" />
</Border>

<!-- PERPETUAL BLOCK -->
<Border x:Name="PerpetualBorder" HorizontalAlignment="Left" Background="Blue" VerticalAlignment="Top" Margin="190,116,0,0" CornerRadius="20" Padding="10" Width="210" Canvas.ZIndex="0">
    <TextBlock x:Name="PerpetualText" Text="Perpetual" Foreground="White" VerticalAlignment="Center" HorizontalAlignment="Center" Margin="0,0,0,0" />
</Border>

<!-- TOGGLE SWITCH -->
<ToggleSwitch x:Name="SubscriptionToggleSwitch" Toggled="SubscriptionToggleSwitch_Toggled" VerticalAlignment="Top" Width="55" Height="35" Margin="199,113,0,10" Canvas.ZIndex="1">
    <!-- Style to hide on/off text -->
    <ToggleSwitch.Resources>
        <Style TargetType="ToggleSwitch">
            <Setter Property="Header" Value=""/>
            <Setter Property="HeaderTemplate">
                <Setter.Value>
                    <DataTemplate>
                        <!-- Empty template to hide the header text -->
                    </DataTemplate>
                </Setter.Value>
            </Setter>
        </Style>
    </ToggleSwitch.Resources>
</ToggleSwitch>
)";
    textBox.Text(xamlSourceCode);
}

void winrt::CppWinUIGallery::implementation::ToggleSwitchPage::CppCodeTextBox_Loaded(
    winrt::Windows::Foundation::IInspectable const &sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto textBox = CppCodeTextBox();

    hstring cppSourceCode = LR"(
void ToggleSwitchPage::SubscriptionToggleSwitch_Toggled(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto toggleSwitch = SubscriptionToggleSwitch();
        auto subscriptionBorder = SubscriptionText().Parent().as<Border>();
        auto perpetualBorder = PerpetualText().Parent().as<Border>();

        SolidColorBrush greenBrush{ Colors::Green() };
        SolidColorBrush blueBrush{ Colors::Blue() };
        SolidColorBrush whiteBrush{ Colors::White() };
        auto customColor = Windows::UI::ColorHelper::FromArgb(58, 56, 245, 212);
        SolidColorBrush customBrush{ customColor };

        if (toggleSwitch.IsOn())
        {
            subscriptionBorder.Background(customBrush);
            perpetualBorder.Background(blueBrush);
            perpetualBorder.Child().as<TextBlock>().Foreground(whiteBrush);
        }
        else
        {
            subscriptionBorder.Background(greenBrush);
            subscriptionBorder.Child().as<TextBlock>().Foreground(whiteBrush);
            perpetualBorder.Background(customBrush);
        }
    }
)";
    textBox.Text(cppSourceCode);
}
