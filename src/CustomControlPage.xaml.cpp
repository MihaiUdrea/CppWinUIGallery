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

    void CustomControlPage::ShowCppButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowCppButton();
        auto textBox = SourceCodeTextBoxCpp();


        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
           /* if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }*/

            // Show XAML source code
            hstring xamlSourceCode = LR"(#include "pch.h"
#include "SettingsCardControl.h"
#include "SettingsCardControl.g.cpp"

namespace winrt::CppWinUIGallery::implementation
{
    // RightSideContent

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_RightSideContentProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"RightSideContent",
            winrt::xaml_typename<Microsoft::UI::Xaml::FrameworkElement>(),
            winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(Microsoft::UI::Xaml::FrameworkElement{nullptr}), Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged}}
    );

    Microsoft::UI::Xaml::FrameworkElement  SettingsCardControl::RightSideContent() // Getter
    {
        return winrt::unbox_value<Microsoft::UI::Xaml::FrameworkElement>(GetValue(m_RightSideContentProperty));
    }

    void SettingsCardControl::RightSideContent(Microsoft::UI::Xaml::FrameworkElement const& value) // Setter
    {
        SetValue(this->m_RightSideContentProperty, winrt::box_value(value));
    }

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::RightSideContentProperty() { return m_RightSideContentProperty; }

    void SettingsCardControl::OnRightSideContentChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& /* e */)
    {
        if (CppWinUIGallery::SettingsCardControl theControl{ d.try_as<CppWinUIGallery::SettingsCardControl>() })
        {
            // Call members of the projected type via theControl.

            CppWinUIGallery::implementation::SettingsCardControl* ptr{ winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }


    // Title

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_TitleProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Title",
            winrt::xaml_typename<hstring>(),
            winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Title"), Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged} }
        );


    hstring SettingsCardControl::Title() // Getter
    {
        return winrt::unbox_value<hstring>(GetValue(this->m_TitleProperty));
    }

    void SettingsCardControl::Title(hstring const& value) // Setter
    {
        SetValue(this->m_TitleProperty, winrt::box_value(value));
    }

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::TitleProperty() { return m_TitleProperty; }

    void SettingsCardControl::OnTitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        if (CppWinUIGallery::SettingsCardControl theControl{ d.try_as<CppWinUIGallery::SettingsCardControl>() })
        {
            // Call members of the projected type via theControl.

            CppWinUIGallery::implementation::SettingsCardControl* ptr{ winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }

    // Subtitle

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_SubTitleProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Subtitle",
            winrt::xaml_typename<hstring>(),
            winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"Subtitle"), Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged} }
        );


    hstring SettingsCardControl::Subtitle() // Getter
    {
        return winrt::unbox_value<hstring>(GetValue(this->m_SubTitleProperty));
    }

    void SettingsCardControl::Subtitle(hstring const& value) // Setter
    {
        SetValue(this->m_SubTitleProperty, winrt::box_value(value));
    }

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::SubtitleProperty() { return m_SubTitleProperty; }

    void SettingsCardControl::OnSubtitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        if (CppWinUIGallery::SettingsCardControl theControl{ d.try_as<CppWinUIGallery::SettingsCardControl>() })
        {
            // Call members of the projected type via theControl.

            CppWinUIGallery::implementation::SettingsCardControl* ptr{ winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }


    // Icon

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_IconProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Icon",
            winrt::xaml_typename<hstring>(),
            winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"\uE700"), Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged} }
        );


    hstring SettingsCardControl::Icon() // Getter
    {
        return winrt::unbox_value<hstring>(GetValue(this->m_IconProperty));
    }

    void SettingsCardControl::Icon(hstring const& value) // Setter
    {
        SetValue(this->m_IconProperty, winrt::box_value(value));
    }

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::IconProperty() { return m_IconProperty; }

    void SettingsCardControl::OnIconChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        if (CppWinUIGallery::SettingsCardControl theControl{ d.try_as<CppWinUIGallery::SettingsCardControl>() })
        {
            // Call members of the projected type via theControl.

            CppWinUIGallery::implementation::SettingsCardControl* ptr{ winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }
})";
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


    void CustomControlPage::ShowIdlButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowIdlButton();
        auto textBox = SourceCodeTextBoxIdl();


        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
           /* if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }*/

            // Show XAML source code
            hstring xamlSourceCode = LR"(namespace CppWinUIGallery
{
    [default_interface]
    runtimeclass SettingsCardControl : Microsoft.UI.Xaml.Controls.Control
    {
        SettingsCardControl();
        
        // right side ContentControl
        static Microsoft.UI.Xaml.DependencyProperty RightSideContentProperty{ get; };
        Microsoft.UI.Xaml.FrameworkElement RightSideContent;

        // title
        static Microsoft.UI.Xaml.DependencyProperty TitleProperty{ get; };
        String Title;

        // sub title
        static Microsoft.UI.Xaml.DependencyProperty SubtitleProperty{ get; };
        String Subtitle;

        // Icon
        static Microsoft.UI.Xaml.DependencyProperty IconProperty{ get; };
        String Icon;
    }
}
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


    void CustomControlPage::ShowHeaderButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHeaderButton();
        auto textBox = SourceCodeTextBoxHeader();


        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
           /* if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }*/

            // Show XAML source code
            hstring xamlSourceCode = LR"(#pragma once
#include "SettingsCardControl.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl>
    {
        SettingsCardControl() { DefaultStyleKey(winrt::box_value(L"CppWinUIGallery.SettingsCardControl")); }

        // RightSideContent

        Microsoft::UI::Xaml::FrameworkElement RightSideContent(); // Getter
        void RightSideContent(Microsoft::UI::Xaml::FrameworkElement const& value); // Setter
        
        static Microsoft::UI::Xaml::DependencyProperty RightSideContentProperty();

        static void OnRightSideContentChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        
        // Title

        hstring Title(); // Getter
        void Title(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty TitleProperty();
        static void OnTitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        // Subtitle

        hstring Subtitle(); // Getter
        void Subtitle(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty SubtitleProperty();
        static void OnSubtitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        // Icon

        hstring Icon(); // Getter
        void Icon(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty IconProperty();
        static void OnIconChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_RightSideContentProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_TitleProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_SubTitleProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_IconProperty;

    };
}
namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl, implementation::SettingsCardControl>
    {
    };
})";
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











