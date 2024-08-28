#include "pch.h"
#include "CustomControlPage.xaml.h"
#if __has_include("CustomControlPage.g.cpp")
#include "CustomControlPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t CustomControlPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void CustomControlPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    

    void CustomControlPage::ShowHideButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();
       

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            hstring xamlSourceCode = LR"(<ResourceDictionary
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:CppWinUIGallery">

    

    <Style TargetType="local:SettingsCardControl" >
        <Setter Property="Template">
            <Setter.Value>
                <ControlTemplate TargetType="local:SettingsCardControl">
                    <Border HorizontalAlignment="Stretch"
                            Background="{ThemeResource CardBackgroundFillColorDefault}"
                            BorderBrush="{ThemeResource CardStrokeColorDefaultBrush}"
                            BorderThickness="1"
                            CornerRadius="6">
                        <Grid Height="60" Margin="15, 0">
                            <Grid.ColumnDefinitions>
                                <ColumnDefinition x:Name="IconColumn" Width="Auto"/>
                                <ColumnDefinition x:Name="TextColumn" Width="*"/>
                                <ColumnDefinition x:Name="ButtonColumn" Width="Auto"/>
                            </Grid.ColumnDefinitions>
                            <FontIcon x:Name="Icon" Glyph="{TemplateBinding Icon}" Foreground="{ThemeResource TextFillColorPrimaryBrush}" Grid.Column="0" Margin="0, 0, 0, 0"/>
                            <StackPanel Orientation="Vertical" Grid.Column="1" HorizontalAlignment="Stretch" VerticalAlignment="Center">
                                <TextBlock 
                                    x:Name="Title"
                                    Text="{TemplateBinding Title}"
                                    Style="{StaticResource FlyoutPickerTitleTextBlockStyle}"
                                    FontSize="15"
                                    Foreground="{ThemeResource TextFillColorPrimaryBrush}"
                                    VerticalAlignment="Top"
                                    Margin="10, 0"/>

                                <TextBlock 
                                    x:Name="Subtitle"
                                    Text="{TemplateBinding Subtitle}"
                                    Style="{StaticResource BaseTextBlockStyle}"
                                    FontSize="10"
                                    Foreground="{ThemeResource TextFillColorSecondaryBrush}"
                                    Opacity="60"
                                    Margin="10, 0"/>


                            </StackPanel>

                            <ContentControl
                                Grid.Column="2"
                                Content="{TemplateBinding RightSideContent}"
                                VerticalAlignment="Center"/>
                        </Grid>
                    </Border>
                </ControlTemplate>
            </Setter.Value>
        </Setter>
    </Style>

    
</ResourceDictionary>
)";
            textBox.Text(xamlSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide Generic.xaml"));
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show Generic.xaml"));
        }
    }
}





//auto button = ShowHideButton();
//auto textBox = SourceCodeTextBox();
//
//
//if (textBox.Visibility() == Visibility::Collapsed)
//{
//    // Hide C++ code if visible
//   /* if (cppTextBox.Visibility() == Visibility::Visible)
//    {
//        cppTextBox.Visibility(Visibility::Collapsed);
//        cppButton.Content(box_value(L"Show C++"));
//    }*/
//
//    // Show XAML source code
//    hstring xamlSourceCode = LR"()";
//    textBox.Text(xamlSourceCode);
//    textBox.Visibility(Visibility::Visible);
//    button.Content(box_value(L"Hide Generic.xaml"));
//}
//else
//{
//    textBox.Visibility(Visibility::Collapsed);
//    button.Content(box_value(L"Show Generic.xaml"));
//}


