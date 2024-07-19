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

    void ToggleSwitchPage::ShowSourceCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Define the XAML source code as a string
            hstring xamlSourceCode =
                L"<Page\n"
                L"    x:Class=\"CppWinUIGallery.ToggleSwitchPage\"\n"
                L"    xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\n"
                L"    xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\"\n"
                L"    xmlns:local=\"using:CppWinUIGallery\"\n"
                L"    xmlns:d=\"http://schemas.microsoft.com/expression/blend/2008\"\n"
                L"    xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\"\n"
                L"    mc:Ignorable=\"d\">\n"
                L"\n"
                L"    <Grid HorizontalAlignment=\"Left\" VerticalAlignment=\"Top\">\n"
                L"        <TextBlock Text=\"ToggleSwitch\" Style=\"{StaticResource TitleLargeTextBlockStyle}\" Margin=\"50,40\"/>\n"
                L"\n"
                L"        <!-- Subscription Border -->\n"
                L"        <Border x:Name=\"SubscriptionBorder\" Background=\"Green\" HorizontalAlignment=\"Left\" VerticalAlignment=\"Top\" Margin=\"40,116,140,0\" CornerRadius=\"20\" Width=\"210\" Canvas.ZIndex=\"0\">\n"
                L"            <TextBlock x:Name=\"SubscriptionText\" Text=\"Subscription\" Foreground=\"White\" HorizontalAlignment=\"Center\" VerticalAlignment=\"Center\" Margin=\"10\" />\n"
                L"        </Border>\n"
                L"\n"
                L"        <!-- Perpetual Border -->\n"
                L"        <Border x:Name=\"PerpetualBorder\" HorizontalAlignment=\"Left\" Background=\"Blue\" VerticalAlignment=\"Top\" Margin=\"190,116,0,0\" CornerRadius=\"20\" Padding=\"10\" Width=\"210\" Canvas.ZIndex=\"0\">\n"
                L"            <TextBlock x:Name=\"PerpetualText\" Text=\"Perpetual\" Foreground=\"White\" VerticalAlignment=\"Center\" HorizontalAlignment=\"Center\" Margin=\"0,0,0,0\" />\n"
                L"        </Border>\n"
                L"\n"
                L"        <!-- ToggleSwitch -->\n"
                L"        <ToggleSwitch x:Name=\"SubscriptionToggleSwitch\" Toggled=\"SubscriptionToggleSwitch_Toggled\" VerticalAlignment=\"Top\" Width=\"55\" Height=\"35\" Margin=\"199,113,0,10\" Canvas.ZIndex=\"1\">\n"
                L"            <!-- Style to hide on/off text -->\n"
                L"            <ToggleSwitch.Resources>\n"
                L"                <Style TargetType=\"ToggleSwitch\">\n"
                L"                    <Setter Property=\"Header\" Value=\"\"/>\n"
                L"                    <Setter Property=\"HeaderTemplate\">\n"
                L"                        <Setter.Value>\n"
                L"                            <DataTemplate>\n"
                L"                                <!-- Empty template to hide the header text -->\n"
                L"                            </DataTemplate>\n"
                L"                        </Setter.Value>\n"
                L"                    </Setter>\n"
                L"                </Style>\n"
                L"            </ToggleSwitch.Resources>\n"
                L"        </ToggleSwitch>\n"
                L"\n"
                L"        <StackPanel Margin=\"45,200\">\n"
                L"            <!-- A Button to show code -->\n"
                L"            <Button x:Name=\"ShowHideButton\" Content=\"Show XAML\" Click=\"ShowSourceCode_Click\" Margin=\"0,0,0,10\"/>\n"
                L"\n"
                L"            <!-- A ScrollViewer to enable scrolling -->\n"
                L"            <ScrollViewer VerticalScrollBarVisibility=\"Auto\" HorizontalScrollBarVisibility=\"Auto\" Height=\"300\">\n"
                L"                <!-- A TextBox to display source code -->\n"
                L"                <TextBox x:Name=\"SourceCodeTextBox\"\n"
                L"                         IsReadOnly=\"True\"\n"
                L"                         AcceptsReturn=\"True\"\n"
                L"                         TextWrapping=\"Wrap\"\n"
                L"                         Margin=\"0\"\n"
                L"                         VerticalAlignment=\"Stretch\"\n"
                L"                         HorizontalAlignment=\"Stretch\"\n"
                L"                         MinWidth=\"300\"\n"
                L"                         Visibility=\"Collapsed\" />\n"
                L"            </ScrollViewer>\n"
                L"        </StackPanel>\n"
                L"    </Grid>\n"
                L"</Page>";

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
}
