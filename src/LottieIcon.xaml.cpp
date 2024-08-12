#include "pch.h"
#include "LottieIcon.xaml.h"
#if __has_include("LottieIcon.g.cpp")
#include "LottieIcon.g.cpp"
#endif
#include "winrt/Windows.UI.Xaml.Media.Animation.h"

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::CppWinUIGallery::implementation
{
    bool isPressedState = false;

    int32_t LottieIcon::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void LottieIcon::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    
   

    void LottieIcon::LottieButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {


        if (LottieButton().IsChecked().GetBoolean() == true)
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
            return;
        }
        else
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
        return;

    }
    void LottieIcon::Button_PointerEntered(IInspectable const& sender, PointerRoutedEventArgs const& e)
    {
    //    if (!isPressedState)
        if (LottieButton().IsChecked().GetBoolean() == true)
            return;
        else
        {

            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"PointerOver");
            return;
        }
    }

    // Handle pointer exiting the button area
    void LottieIcon::Button_PointerExited(IInspectable const& sender, PointerRoutedEventArgs const& e)
    {
        if (LottieButton().IsChecked().GetBoolean() == false
            )
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
        }
        else
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
            return;
        }
    }
    void LottieIcon::InitializeIconState()
    {
       
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
    }
    void LottieIcon::LottieButton_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        InitializeIconState();
    }
    void LottieIcon::ShowSourceCode_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();


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
<ToggleButton Loaded="LottieButton_Loaded"  Width="75" IsEnabled="True" x:Name="LottieButton" Margin="0,10,0,10"  Click="LottieButton_Click" PointerExited="Button_PointerExited" PointerEntered="Button_PointerEntered">
                   

                    <AnimatedIcon x:Name="SearchAnimatedIcon">
                        <AnimatedIcon.Source>
                            <local:AnimatedLogo/>
                        </AnimatedIcon.Source>
                        <AnimatedIcon.FallbackIconSource>
                            <SymbolIconSource Symbol="GlobalNavigationButton"/>
                        </AnimatedIcon.FallbackIconSource>
                    </AnimatedIcon>
                </ToggleButton>
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
    

}




