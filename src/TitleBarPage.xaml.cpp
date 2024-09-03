#include "pch.h"

#include "TitleBarPage.xaml.h"
#if __has_include("TitleBarPage.g.cpp")
#include "TitleBarPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
int32_t TitleBarPage::MyProperty()
{
    throw hresult_not_implemented();
}

void TitleBarPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void TitleBarPage::ShowHideButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                                        winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto button = ShowHideButton();
    auto textBox = SourceCodeTextBox();
    auto stackPanel = ShowHideStackPanel_xaml();
    Controls::ScrollViewer scrollviewer;

    for (auto el : stackPanel.Children())
    {
        if (auto s = el.try_as<Controls::ScrollViewer>())
            scrollviewer = s; // capture stackpanel's scrollviewer for actual height of the visible text box
    }

    if (textBox.Visibility() == Visibility::Collapsed)
    {
        // Hide C++ code if visible
        /* if (cppTextBox.Visibility() == Visibility::Visible)
         {
             cppTextBox.Visibility(Visibility::Collapsed);
             cppButton.Content(box_value(L"Show C++"));
         }*/

        // Show XAML source code
        hstring xamlSourceCode = LR"( <Grid x:Name="AppTitleBar"
                    Loaded="AppTitleBar_Loaded"
                    SizeChanged="AppTitleBar_SizeChanged"
                    Height="48"
                    Grid.Row="0"
                    Grid.Column="0">

            <Grid.ColumnDefinitions>
                <ColumnDefinition x:Name="BackButtonColumn" Width="48"/>
                <ColumnDefinition x:Name="IconColumn" Width="Auto"/>
                <ColumnDefinition x:Name="TitleColumn" Width="Auto"/>
            </Grid.ColumnDefinitions>

            <Button x:Name="TitleBar_BackButton"
                    Click="TitleBar_BackButton_Click"
                    Style="{StaticResource NavigationBackButtonNormalStyle}"
                    Foreground="{StaticResource BackButtonDisabledForegroundThemeBrush}"
                    HorizontalContentAlignment="Center"
                    VerticalAlignment="Center"
                    IsEnabled="False"/>

            <Image x:Name="TitleBarIcon"
                   Source="ms-appx:///Assets/caphyon_logo.png"
                   Grid.Column="1"
                   VerticalAlignment="Center"
                   Width="20" Height="20"
                   Margin="15,0,0,0"/>
            <TextBlock x:Name="TitleBarTextBlock"
               Text="Cpp WinUI 3 Gallery" 
               Style="{StaticResource CaptionTextBlockStyle}"
               Grid.Column="2"
               VerticalAlignment="Center"
               Margin="15,0,0,0"/>
        </Grid>})";
        textBox.Text(xamlSourceCode);
        textBox.Visibility(Visibility::Visible);
        button.Content(box_value(L"Hide XAML"));
        auto myMargin = stackPanel.Margin();
        myMargin.Bottom = 0; // Get the margin value and update the buttom parameter
        stackPanel.Margin(myMargin);
    }
    else
    {
        textBox.Visibility(Visibility::Collapsed);
        button.Content(box_value(L"Show XAML"));
        auto myMargin = stackPanel.Margin();
        myMargin.Bottom = -1 * scrollviewer.ActualHeight();
        stackPanel.Margin(myMargin);
    }
}

void TitleBarPage::ShowCppButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                                       winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto button = ShowCppButton(); // Make sure the button is named correctly
    auto textBox = CppCodeTextBox();
    auto stackPanel = ShowHideStackPanel_cpp();
    Controls::ScrollViewer scrollviewer;

    for (auto el : stackPanel.Children())
    {
        if (auto s = el.try_as<Controls::ScrollViewer>())
            scrollviewer = s; // capture stackpanel's scrollviewer for actual height of the visible text box
    }

    if (textBox.Visibility() == Visibility::Collapsed)
    {
        // Hide XAML code if visible
        /* if (xamlTextBox.Visibility() == Visibility::Visible)
         {
             xamlTextBox.Visibility(Visibility::Collapsed);
             xamlButton.Content(box_value(L"Show XAML"));
         }*/

        // Show C++ source code
        hstring cppSourceCode = LR"(MainWindow::MainWindow()
    {
        InitializeComponent();
        ExtendsContentIntoTitleBar(true);
        this->AppWindow().TitleBar().PreferredHeightOption(Microsoft::UI::Windowing::TitleBarHeightOption::Standard);
        
        // THIS IS NOT WORKING ON CURRENT WINDOWS APP SDK VERSION 
        // WARNING GetForCurrentView automatically throws an exception as the method is no longer supported
        // Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().SetPreferredMinSize(Windows::Foundation::Size(500, 300));
        
    }

    void MainWindow::SetRegionsForCustomTitleBar()
    {
        double scaleAdjustment = AppTitleBar().XamlRoot().RasterizationScale();
        auto m_AppWindow = this->AppWindow();

        
        Windows::Foundation::Rect bounds;
        std::vector<Windows::Graphics::RectInt32> rects;
        

        // Setting sstem capture buttons margin

        AppTitleBar().Margin(ThicknessHelper::FromLengths(0, 0, m_AppWindow.TitleBar().RightInset(), 0));
        AppTitleBar().Width(m_AppWindow.ClientSize().Width - m_AppWindow.TitleBar().RightInset());


        // Setting custom tall title bar drag region
        
        auto transform = AppTitleBar().TransformToVisual(nullptr);
        bounds = transform.TransformBounds(Windows::Foundation::Rect
            { 0, 0, (float)AppTitleBar().ActualWidth(), (float)AppTitleBar().ActualHeight() });

        Windows::Graphics::RectInt32 TitleBarRect = GetRect(bounds, scaleAdjustment);

        rects = { TitleBarRect };
        auto rectArray = array_view<Windows::Graphics::RectInt32>(rects);

        this->AppWindow().TitleBar().SetDragRectangles(rectArray);

        rects.clear();


        // Setting back button custom nno-dragable region

        transform = TitleBar_BackButton().TransformToVisual(nullptr);

        bounds = transform.TransformBounds(Windows::Foundation::Rect
            { 0, 0, (float)TitleBar_BackButton().ActualWidth(), (float)TitleBar_BackButton().ActualHeight() });

        Windows::Graphics::RectInt32 BackButtonRect = GetRect(bounds, scaleAdjustment);


        rects = { BackButtonRect };
        rectArray = array_view<Windows::Graphics::RectInt32>(rects);

        
        InputNonClientPointerSource nonClientInputSrc = InputNonClientPointerSource::GetForWindowId(this->AppWindow().Id());
        nonClientInputSrc.SetRegionRects(NonClientRegionKind::Passthrough, rectArray);


        
    })";
        textBox.Text(cppSourceCode);
        textBox.Visibility(Visibility::Visible);
        button.Content(box_value(L"Hide C++"));
        auto myMargin = stackPanel.Margin();
        myMargin.Bottom = 0; // Get the margin value and update the buttom parameter
        stackPanel.Margin(myMargin);
    }
    else
    {
        textBox.Visibility(Visibility::Collapsed);
        button.Content(box_value(L"Show C++"));
        auto myMargin = stackPanel.Margin();
        myMargin.Bottom = -1 * scrollviewer.ActualHeight();
        stackPanel.Margin(myMargin);
    }
}
} // namespace winrt::CppWinUIGallery::implementation
