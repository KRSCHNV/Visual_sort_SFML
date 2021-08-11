#include "funcs.hpp"

void generate_array(elem arr[], int length, float elem_width, float height_one, sf::RenderWindow &w)
{
    unordered_map<int, bool> added;
    mt19937 gen(time(0));
    
    for (int i = 0; i < length; i++)
    {
        bool flag = false;
        while (!flag)
        {
            uniform_int_distribution<> uid(0, 511);
            int random = uid(gen);
            
            if (!added.count(random))
            {
                added[random] = true;
                flag = true;
                sf::RectangleShape sh;
                sh.setSize(sf::Vector2f(elem_width, height_one * random));
                sh.setFillColor(sf::Color::Black);
                sh.setOrigin(0, sh.getSize().y);
                sh.setPosition(w.getSize().x * 0.1 + i * elem_width, w.getSize().y * 0.75f);
                elem new_elem = {sh, random};
                arr[i] = new_elem;
            }
        }
    }
}

void draw_array(elem arr[], int length, sf::RenderWindow &w)
{
    for (int i = 0; i < length; i++)
        w.draw(arr[i].shape);
}

void swap_elements (elem a[], int index_1, int index_2)
{
    elem dop = a[index_1]; usleep(90);
    sf::Vector2f pos;
    pos = a[index_2].shape.getPosition();
    
    a[index_1] = a[index_2]; usleep(90);
    a[index_2] = dop; usleep(90);
    a[index_1].shape.setPosition(dop.shape.getPosition());
    a[index_2].shape.setPosition(pos);
}

void selection_sort (elem a[], int size)
{
    int min = a[0].value, min_index;
    
    for (int i = 0 ; i < size; i++)
    {
        min_index = i; usleep(90);
        min = a[i].value; usleep(90);
        usleep(90);
        for (int j = i; j < size; j++)
        {
            usleep(90);
            if (a[j].value< min)
            {
                min = a[j].value; usleep(90);
                min_index = j; usleep(90);
            }
        }
        swap_elements(a, i, min_index); usleep(90);
    }
}

void insertion_sort(elem arr[], int size)
{
    sf::Vector2f pos;
    
    for (int j = 1; j < size; j++)
    {
        elem key = arr[j]; usleep(90);
        int i = j - 1; usleep(90);
        usleep(90);
        while ((i >= 0) && (arr[i].value > key.value))
        {
            pos =  arr[i + 1].shape.getPosition();
            arr[i + 1] = arr[i]; usleep(90);
            arr[i + 1].shape.setPosition(pos);
            i = i - 1; usleep(90);
        }
        
        pos =  arr[i + 1].shape.getPosition();
        arr[i + 1] = key; usleep(90);
        arr[i + 1].shape.setPosition(pos);
    }
}

int partition (elem arr[], int low, int high)
{
    mt19937 gen(time(0)); usleep(90);
    uniform_int_distribution<> uid(low, high); usleep(90);
    int random = uid(gen); usleep(90);
    swap_elements(arr, random, high); usleep(90);
    
    int pivot = arr[high].value;  usleep(90);
    int i = (low - 1);  usleep(90);
 
    for (int j = low; j < high; j++)
    {
        usleep(90);
        if (arr[j].value < pivot)
        {
            i++; usleep(90);
            swap_elements(arr, i, j);  usleep(90);
        }
    }
    swap_elements(arr, i + 1, high);  usleep(90);
    return (i + 1);
}
 
void quick_sort(elem arr[], int low, int high)
{
    usleep(90);
    if (low < high)
    {
        int pi = partition(arr, low, high);  usleep(90);
        quick_sort(arr, low, pi - 1);  usleep(90);
        quick_sort(arr, pi + 1, high);  usleep(90);
    
    }
}

int merge (elem* a, int p, int q, int r)
{
    elem* pq = new elem[(q - p) + 1]; usleep(90);
    elem* qr = new elem[r - q]; usleep(90);
    sf::Vector2f pos;
    
    int j = p; usleep(90);
    for (int i = 0; i < q - p + 1; i++)
    {
        pq[i] = a[j]; usleep(90);
        j++; usleep(90);
    }
    
    j = q + 1; usleep(90);
    for (int i = 0; i < r - q; i++)
    {
        qr[i] = a[j]; usleep(90);
        j++; usleep(90);
    }
    
    int i = p, k = 0; usleep(90);
    j = 0; usleep(90);
    while ((j < q - p + 1) && (k < r - q))
    {
        pos = a[i].shape.getPosition(); usleep(90);
        usleep(90);
        if (pq[j].value < qr[k].value)
        {
            a[i] = pq[j]; usleep(90);
            j++; usleep(90);
        }
        else
        {
            a[i] = qr[k]; usleep(90);
            k++; usleep(90);
        }
        a[i].shape.setPosition(pos); usleep(90);
        i++; usleep(90);
    }
    
    usleep(90);
    if (j == q - p + 1)
    {
        for (k; k < r - q; k++)
        {
            pos = a[i].shape.getPosition(); usleep(90);
            a[i] = qr[k]; usleep(90);
            a[i].shape.setPosition(pos); usleep(90);
            i++; usleep(90);
        }
    }
    else if (k == r - q)
    {
        for (j; j < q - p + 1; j++)
        {
            pos = a[i].shape.getPosition(); usleep(90);
            a[i] = pq[j]; usleep(90);
            a[i].shape.setPosition(pos); 
            i++; usleep(90);
        }
    }
    
    delete[] pq;
    delete[] qr;
    return 0;
}

void merge_sort (elem a[], int p, int r)
{
    usleep(90);
    if (p < r)
    {
        int q = (p + r)/2; usleep(90);
        merge_sort(a, p, q); usleep(90);
        merge_sort(a, q + 1, r); usleep(90);
        merge(a, p, q, r); usleep(90);
    }
}

bool mouse_on_button (sf::Mouse m, sf::RenderWindow &w, button b)
{
    if ((m.getPosition(w).x > b.body.getPosition().x) && (m.getPosition(w).x < b.body.getPosition().x + b.body.getLocalBounds().width))
    {
        if ((m.getPosition(w).y > b.body.getPosition().y) && (m.getPosition(w).y < b.body.getPosition().y + b.body.getLocalBounds().height))
            return  true;
        else
            return false;
    }
    else
        return false;
}

void init_button (button &b, float pos_x, float pos_y, sf::Color b_color, string text, sf::Font &font, sf::Color t_color, float t_size, sf::RenderWindow &w)
{
    //инициализация текста
    b.text.setFont(font);
    b.text.setString(text);
    b.text.setCharacterSize(w.getSize().y * t_size);
    b.text.setFillColor(t_color);
    b.text.setPosition(w.getSize().x * pos_x + b.text.getLocalBounds().height / 2.f, w.getSize().y * pos_y);
    //инициализация тела
    sf::RectangleShape sh_b(sf::Vector2f(b.text.getLocalBounds().width * 1.045f + b.text.getLocalBounds().height, b.text.getLocalBounds().height * 2));
    b.body = sh_b;
    b.body.setFillColor(b_color);
    b.body.setPosition(w.getSize().x * pos_x, w.getSize().y * pos_y);
}

void color_button (button &b, sf::Color b_color, sf::Color t_color)
{
    b.body.setFillColor(b_color);
    b.text.setFillColor(t_color);
}

void init_radio_button (radio_button &rb, float pos_x, float pos_y, sf::Color b_color, string text, sf::Font &font, sf::Color t_color, float t_size, sf::RenderWindow &w, sortt type)
{
    //инициализация заднего плана
    sf::CircleShape sh_b(t_size * w.getSize().y / 4.f);
    rb.background = sh_b;
    rb.background.setFillColor(b_color);
    rb.background.setPosition(w.getSize().x * pos_x, w.getSize().y * pos_y);
    
    //инициализация переднего плана
    sf::CircleShape sh_b2(sh_b.getRadius() * 0.7);
    rb.foreground = sh_b2;
    rb.foreground.setFillColor(sf::Color::Black);
    rb.foreground.setPosition(rb.background.getPosition().x + (rb.background.getLocalBounds().width - rb.foreground.getLocalBounds().width) / 2,
                              rb.background.getPosition().y + (rb.background.getLocalBounds().height - rb.foreground.getLocalBounds().height) / 2);
    
    //инициализация текста
    sf::Glyph R = font.getGlyph('R', t_size * w.getSize().y, 0); //для более ровного положения текста
    float max_height = R.bounds.height;
    rb.text.setFont(font);
    rb.text.setString(text);
    rb.text.setCharacterSize(w.getSize().y * t_size);
    rb.text.setFillColor(t_color);
    rb.text.setPosition(rb.background.getPosition().x + rb.background.getLocalBounds().width * 1.2f,
                        rb.background.getPosition().y - max_height / 2 - (max_height - rb.background.getLocalBounds().height) / 2);
    
    rb.sort_type = type;
}

bool mouse_on_radio_button (sf::Mouse m, sf::RenderWindow &w, radio_button rb)
{
    if ((m.getPosition(w).x > rb.background.getPosition().x) && (m.getPosition(w).x < rb.background.getPosition().x + rb.background.getLocalBounds().width))
    {
        if ((m.getPosition(w).y > rb.background.getPosition().y) && (m.getPosition(w).y < rb.background.getPosition().y + rb.background.getLocalBounds().height))
            return true;
        else
            return false;
    }
    
    return false;
}

void bubble_sort (elem a[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        usleep(90);
        for (int j = 0; j < size - 1 - i; j++)
        {
            usleep(90);
            if (a[j].value > a[j + 1].value)
                swap_elements(a, j, j + 1); usleep(90);
        }
    }
}

int parent (int i)
{
    return i/2;
}

int left (int i)
{
    return 2 * i;
}

int right (int i)
{
    return 2 * i + 1;
}

void max_heapify (elem a[], int i, int heap_size)
{
    int l = left(i), r = right(i), largest; usleep(90);
    
    if ((l <= heap_size) && (a[l].value > a[i].value))
        largest = l;
    else
        largest = i;
    if ((r <= heap_size) && (a[r].value > a[largest].value))
        largest = r;
    if (largest != i)
    {
        swap_elements(a, i, largest); usleep(90);
        max_heapify(a, largest, heap_size); usleep(90);
    }
}

void build_max_heap (elem a[], int length, int &heap_size)
{
    heap_size = length; usleep(90);
    for (int i = length / 2; i >= 0; i--)
    max_heapify(a, i, heap_size); usleep(90);
}

void heap_sort (elem a[], int length, int heap_size)
{
    build_max_heap(a, length, heap_size); usleep(90);
    for (int i = length; i >= 1; i--)
    {
        swap_elements(a, 0, i); usleep(90);
        heap_size--; usleep(90);
        max_heapify(a, 0, heap_size); usleep(90);
    }
}

void counting_sort (elem b[], elem a[], int k, int length) //массивы поставлены наоборот, чтобы можно было заметить визуализацию 
{
    sf::Vector2f pos;
    
    int* c = new int[k + 1]; usleep(90);
    for (int i = 0; i <= k; i++)
    c[i] = 0; usleep(90);
    
    for (int j = 0; j < length; j++)
    c[a[j].value] += 1; usleep(90);
    
    for (int i = 1; i <= k; i++)
    c[i] += c[i - 1]; usleep(90);
    
    for (int j = length - 1; j >= 0; j--)
    {
        pos =  b[c[a[j].value] - 1].shape.getPosition();
        b[c[a[j].value] - 1] = a[j]; usleep(90);
        
        b[c[a[j].value] - 1].shape.setPosition(pos);
        c[a[j].value] -= 1; usleep(90);
    }
}
