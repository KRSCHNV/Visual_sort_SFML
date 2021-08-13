#include "funcs.hpp"
int main(int, char const**)
{
    //Настройка и создание окна
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.6f, sf::VideoMode::getDesktopMode().height * 0.6f), "Visual sort", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    
    //Интерфейс
    sf::Font QlassikBold, Abril;
    QlassikBold.loadFromFile("/Users/vladimirkorsunov/Desktop/Programming/SFML_learn/visual_sort/visual_sort/QlassikBold_TB.otf");
    Abril.loadFromFile("/Users/vladimirkorsunov/Desktop/Programming/SFML_learn/visual_sort/visual_sort/AbrilFatface-Regular.ttf");
    
    sf::Mouse mouse;
    sf::Cursor cur_arrow, cur_hand;
    cur_arrow.loadFromSystem(sf::Cursor::Arrow);
    cur_hand.loadFromSystem(sf::Cursor::Hand);
    
    sf::RectangleShape background, background2, devide_line_1;
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y * 0.25f));
    background.setPosition(0, window.getSize().y * 0.75f);
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(-3.f);
    background.setOutlineColor(sf::Color(110, 40, 40, 255));
    
    background2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y * 0.125));
    background2.setPosition(0, 0);
    background2.setFillColor(sf::Color::Black);
    background2.setOutlineThickness(-3.f);
    background2.setOutlineColor(sf::Color(110, 40, 40, 255));
    
    sf::Text sort_info;
    sort_info.setCharacterSize(window.getSize().y * 0.045);
    sort_info.setFont(Abril);
    sort_info.setFillColor(sf::Color(110, 40, 40));
    sort_info.setString("WORST-CASE - O(n^2) | AVERAGE - O(n^2) | BEST-CASE - O(n)");
    sf::Glyph g = QlassikBold.getGlyph('|', window.getSize().y * 0.0625, false);
    sort_info.setPosition((window.getSize().x - sort_info.getLocalBounds().width) / 2, (background2.getSize().y) / 2 - g.bounds.height / 2);
    
    button generate_array_btn, go_btn, back_btn;
    init_button(generate_array_btn, 0.005, 0.77, sf::Color(110, 40, 40), "GENERATE ARRAY", QlassikBold, sf::Color::Black, 0.035, window);
    init_button(go_btn, 0.005, 0.85, sf::Color(110, 40, 40), "GO!", QlassikBold, sf::Color::Black, 0.035, window);
    init_button(back_btn, 0.005, 0.93, sf::Color(110, 40, 40), "BACK!", QlassikBold, sf::Color::Black, 0.035, window);
    button button_arr[3] = {generate_array_btn, go_btn, back_btn};
    bool button_flag = false;
    
    devide_line_1.setSize(sf::Vector2f(window.getSize().x * 0.0025, window.getSize().y * 0.25));
    devide_line_1.setPosition(2 * generate_array_btn.body.getPosition().x + generate_array_btn.body.getLocalBounds().width - 3, background.getPosition().y);
    devide_line_1.setFillColor(sf::Color(110, 40, 40));
    
    radio_button bubble_sort_rb, selection_sort_rb, insertion_sort_rb, quick_sort_rb, merge_sort_rb, heap_sort_rb, counting_sort_rb, radix_sort_rb;
    init_radio_button(bubble_sort_rb, 0.17, 0.77, sf::Color(110, 40, 40), "BUBBLE SORT", QlassikBold, sf::Color::White, 0.055, window, bubble_sort_en);
    init_radio_button(selection_sort_rb, 0.47, 0.77, sf::Color(110, 40, 40), "SELECTION SORT", QlassikBold, sf::Color::White, 0.055, window, selection_sort_en);
    init_radio_button(insertion_sort_rb, 0.77, 0.77, sf::Color(110, 40, 40), "INSERTION SORT", QlassikBold, sf::Color::White, 0.055, window, insertion_sort_en);
    init_radio_button(quick_sort_rb, 0.17, 0.85, sf::Color(110, 40, 40), "QUICK SORT", QlassikBold, sf::Color::White, 0.055, window, quick_sort_en);
    init_radio_button(merge_sort_rb, 0.47, 0.85, sf::Color(110, 40, 40), "MERGE SORT", QlassikBold, sf::Color::White, 0.055, window, merge_sort_en);
    init_radio_button(heap_sort_rb, 0.77, 0.85, sf::Color(110, 40, 40), "HEAP SORT", QlassikBold, sf::Color::White, 0.055, window, heap_sort_en);
    init_radio_button(counting_sort_rb, 0.17, 0.93, sf::Color(110, 40, 40), "COUNTING SORT", QlassikBold, sf::Color::White, 0.055, window, counting_sort_en);
    init_radio_button(radix_sort_rb, 0.77, 0.93, sf::Color(110, 40, 40), "RADIX SORT", QlassikBold, sf::Color::White, 0.055, window, radix_sort_en);
    radio_button radio_button_arr[8] = {bubble_sort_rb, selection_sort_rb, insertion_sort_rb, quick_sort_rb, merge_sort_rb, heap_sort_rb, counting_sort_rb, radix_sort_rb};
    radio_button_arr[0].checked = true;
    bool radio_button_flag = false;
    
    //Инициализация массива
    elem array[512], old_array[512], plus_array[512];
    float el_w = (window.getSize().x * 0.8f) / 512.f;
    float el_h = (window.getSize().y * 0.6f) / 512.f;
    generate_array(array, 512, el_w, el_h, window);
    copy(begin(array), end(array), begin(old_array));
    copy(begin(array), end(array), begin(plus_array));
    
    int heap_size; //для сортировки кучей
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse_on_button(mouse, window, button_arr[0]))
                {
                    copy(begin(array), end(array), begin(old_array));
                    generate_array(array, 512, el_w, el_h, window);
                }
                else if (mouse_on_button(mouse, window, button_arr[1]))
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (radio_button_arr[i].checked)
                        {
                            copy(begin(array), end(array), begin(old_array));
                            
                            if (radio_button_arr[i].sort_type == bubble_sort_en)
                            {
                                thread th(bubble_sort, array, 512);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == selection_sort_en)
                            {
                                thread th(selection_sort, array, 512);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == insertion_sort_en)
                            {
                                thread th(insertion_sort, array, 512);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == quick_sort_en)
                            {
                                thread th(quick_sort, array, 0, 511);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == merge_sort_en)
                            {
                                thread th(merge_sort, array, 0, 511);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == heap_sort_en)
                            {
                                thread th(heap_sort, array, 511, heap_size);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == counting_sort_en)
                            {
                                thread th(counting_sort, array, plus_array, 511, 512, false, 1);
                                th.detach();
                            }
                            else if (radio_button_arr[i].sort_type == radix_sort_en)
                            {
                                thread th(radix_sort, array, plus_array, 512);
                                th.detach();
                            }
                        }
                    }
                }
                else if (mouse_on_button(mouse, window, button_arr[2]))
                    copy(begin(old_array), end(old_array), begin(array));
                
                for (int i = 0; i < 8; i++)
                {
                    if (mouse_on_radio_button(mouse, window, radio_button_arr[i]))
                    {
                        radio_button_arr[i].checked = true;
                        switch (radio_button_arr[i].sort_type) {
                            case bubble_sort_en:
                                sort_info.setString("WORST-CASE - O(n^2) | AVERAGE - O(n^2) | BEST-CASE - O(n)");
                                break;
                            case selection_sort_en:
                                sort_info.setString("WORST-CASE - O(n^2) | AVERAGE - O(n^2) | BEST-CASE - O(n^2)");
                                break;
                            case insertion_sort_en:
                                sort_info.setString("WORST-CASE - O(n^2) | AVERAGE - O(n^2) | BEST-CASE - O(n)");
                                break;
                            case quick_sort_en:
                                sort_info.setString("WORST-CASE - O(n^2) | AVERAGE - O(n*log(n)) | BEST-CASE - O(n*log(n))");
                                break;
                            case merge_sort_en:
                                sort_info.setString("WORST-CASE - O(n*log(n)) | AVERAGE - O(n*log(n)) | BEST-CASE - O(n*log(n))");
                                break;
                            case heap_sort_en:
                                sort_info.setString("WORST-CASE - O(n*log(n)) | AVERAGE - O(n*log(n)) | BEST-CASE - O(n*log(n))");
                                break;
                            case counting_sort_en:
                                sort_info.setString("WORST-CASE - O(k) | AVERAGE - O(n+k) | BEST-CASE - O(n)");
                                break;
                            case radix_sort_en:
                                sort_info.setString("WORST-CASE - O(n*lg(n)) | AVERAGE - O(n*lg(n)) | BEST-CASE - O(n*lg(n))");
                                break;
                            default:
                                break;
                        }
                        sort_info.setPosition((window.getSize().x - sort_info.getLocalBounds().width) / 2, (background2.getSize().y) / 2 - g.bounds.height / 2);
                        for (int j = 0; j < 8; j++)
                        {
                            if (j != i)
                                radio_button_arr[j].checked = false;
                        }
                    }
                }
            }
        }
        
        //обработка наведения на кнопки
        for (int i = 0; i < 3; i++)
        {
            if (mouse_on_button(mouse, window, button_arr[i]))
            {
                color_button(button_arr[i], sf::Color(45, 33, 33), sf::Color(110, 40, 40));
                button_flag = true;
            }
            else
                color_button(button_arr[i], sf::Color(110, 40, 40), sf::Color::Black);
        }
        button_flag ? window.setMouseCursor(cur_hand) : window.setMouseCursor(cur_arrow);
        
        //обработка наведения radio button
        if (!button_flag)
        {
            for (int i = 0; i < 8; i++)
            {
                if (mouse_on_radio_button(mouse, window, radio_button_arr[i]))
                    radio_button_flag = true;
            }
            radio_button_flag ? window.setMouseCursor(cur_hand) : window.setMouseCursor(cur_arrow);
            radio_button_flag = false;
        }
        button_flag = false;
        
        //отрисовка
        window.clear(sf::Color(87, 87, 87, 255));
        window.draw(background);
        window.draw(background2);
        window.draw(sort_info);
        draw_array(array, 512, window);
        for (int i = 0; i < 3; i++)
        {
            window.draw(button_arr[i].body);
            window.draw(button_arr[i].text);
        }
        window.draw(devide_line_1);
        for (int i = 0; i < 8; i++)
        {
            window.draw(radio_button_arr[i].background);
            if (radio_button_arr[i].checked)
                window.draw(radio_button_arr[i].foreground);
            window.draw(radio_button_arr[i].text);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
