#include "pch.h"
#include "ConnectedAnimation.xaml.h"
#if __has_include("ConnectedAnimation.g.cpp")
#include "ConnectedAnimation.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Media::Animation;
using namespace std::chrono;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t ConnectedAnimation::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ConnectedAnimation::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ConnectedAnimation::OnPointerEnter(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {

        if (!m_pointerInside)
        {

            m_pointerInside = true;
            if (!m_hovered && !m_animationInProgress)
            {
                m_hovered = true;
                m_animationInProgress = true;
                helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

                HoverUpStoryboard().Begin();

           
                auto timer = winrt::Microsoft::UI::Xaml::DispatcherTimer();

                timer.Interval(std::chrono::milliseconds(600));

           
                timer.Tick([this, timer](IInspectable const&, IInspectable const&)
                    {
                        if (blueStackPanel() && blueStackPanel().Children().Size() > 0)
                        {
                            auto rectangle = blueStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Shapes::Rectangle>();
                            if (rectangle)
                            {
                                rectangle.Fill(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 53, 48, 54)));
                                auto sizeUpStoryboard = sizeUp();

                                sizeUpStoryboard.Completed([this](IInspectable const&, IInspectable const&)
                                    {
                                        m_animationInProgress = false; 
                                        if (!m_pointerInside) 
                                        {
                                            
                                  
                                            sizeDown().Begin();
                                            m_hovered = false;
                                            m_animationInProgress = false;
                                            

                                            if (blueStackPanel() && blueStackPanel().Children().Size() > 0)
                                            {
                                                auto rectangle = blueStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Shapes::Rectangle>();
                                                if (rectangle)
                                                {
                                                    auto gradientBrush = Microsoft::UI::Xaml::Media::LinearGradientBrush();
                                                    gradientBrush.StartPoint({ 0, 0 });
                                                    gradientBrush.EndPoint({ 1, 1 });

                                                    gradientBrush.GradientStops().Clear();

                                                    auto stop1 = Microsoft::UI::Xaml::Media::GradientStop();
                                                    stop1.Color(Windows::UI::ColorHelper::FromArgb(255, 52, 78, 183)); // #344EB7
                                                    stop1.Offset(0.0);
                                                    gradientBrush.GradientStops().Append(stop1);

                                                    auto stop2 = Microsoft::UI::Xaml::Media::GradientStop();
                                                    stop2.Color(Windows::UI::ColorHelper::FromArgb(255, 61, 84, 178)); // #3D54B2
                                                    stop2.Offset(0.2);
                                                    gradientBrush.GradientStops().Append(stop2);

                                                    auto stop3 = Microsoft::UI::Xaml::Media::GradientStop();
                                                    stop3.Color(Windows::UI::ColorHelper::FromArgb(255, 108, 128, 211)); // #6C80D3
                                                    stop3.Offset(0.8);
                                                    gradientBrush.GradientStops().Append(stop3);

                                                    auto stop4 = Microsoft::UI::Xaml::Media::GradientStop();
                                                    stop4.Color(Windows::UI::ColorHelper::FromArgb(255, 92, 110, 184)); // #5C6EB8
                                                    stop4.Offset(0.7);
                                                    gradientBrush.GradientStops().Append(stop4);

                                                    rectangle.Fill(gradientBrush);
                                                    helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

                                                }

                                            }
                                            OnPointerExit(nullptr, nullptr);

                                        }
                                       

                                    
                                    });
                                auto rectangle = blueStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Shapes::Rectangle>();

                                rectangle.Fill(SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 53, 48, 54)));
                                

                                if (helperStackPanel()  )
                                {
                                    helperStackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
                                    helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
                                     sizeUpStoryboard.Begin();

                                     helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
                                }
                               
                            }
                        }
                        timer.Stop();
                    });
               

                timer.Start();
         
            }
          
        }
    }

    void ConnectedAnimation::OnPointerExit(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        try
        {
            if (m_pointerInside)
            {
                m_pointerInside = false;
                if (m_hovered && !m_animationInProgress)
                {
                    m_hovered = false;
                    m_animationInProgress = false; // Set the flag to indicate an animation is in progress
                    /* HoverDownStoryboard().Begin(); */
                 
                    helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

                    // Make helperStackPanel visible and collapse helper2StackPanel
             
                    if (blueStackPanel() && blueStackPanel().Children().Size() > 0)
                    {
                        auto rectangle = blueStackPanel().Children().GetAt(0).as<Microsoft::UI::Xaml::Shapes::Rectangle>();
                        if (rectangle)
                        {
                            auto gradientBrush = Microsoft::UI::Xaml::Media::LinearGradientBrush();
                            gradientBrush.StartPoint({ 0, 0 });
                            gradientBrush.EndPoint({ 1, 1 });

                            gradientBrush.GradientStops().Clear();

                            auto stop1 = Microsoft::UI::Xaml::Media::GradientStop();
                            stop1.Color(Windows::UI::ColorHelper::FromArgb(255, 52, 78, 183)); // #344EB7
                            stop1.Offset(0.0);
                            gradientBrush.GradientStops().Append(stop1);

                            auto stop2 = Microsoft::UI::Xaml::Media::GradientStop();
                            stop2.Color(Windows::UI::ColorHelper::FromArgb(255, 61, 84, 178)); // #3D54B2
                            stop2.Offset(0.2);
                            gradientBrush.GradientStops().Append(stop2);

                            auto stop3 = Microsoft::UI::Xaml::Media::GradientStop();
                            stop3.Color(Windows::UI::ColorHelper::FromArgb(255, 108, 128, 211)); // #6C80D3
                            stop3.Offset(0.8);
                            gradientBrush.GradientStops().Append(stop3);

                            auto stop4 = Microsoft::UI::Xaml::Media::GradientStop();
                            stop4.Color(Windows::UI::ColorHelper::FromArgb(255, 92, 110, 184)); // #5C6EB8
                            stop4.Offset(0.7);
                            gradientBrush.GradientStops().Append(stop4);

                            rectangle.Fill(gradientBrush);
                        }
                    }

                    // Attach Completed event to reset the flag when the animation is done
                    auto sizeDownStoryboard = sizeDown();
                    sizeDownStoryboard.Completed([this](IInspectable const&, IInspectable const&)
                        {
                            m_animationInProgress = false; // Reset the flag
                        });

                    
                    if (helperStackPanel() && helper2StackPanel())
                    {
                        helperStackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
                        helper2StackPanel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
                    }
                    sizeDownStoryboard.Begin();
                 


                }
            }
        }
        catch (const std::exception& ex)
        {
            OutputDebugStringA(ex.what());
        }
    }



}