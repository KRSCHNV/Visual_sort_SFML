#ifndef funcs_hpp
#define funcs_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <unordered_map>
#include <iostream>
#include <unistd.h>
#include <thread>
using namespace std;

struct elem //структура элемента
{
    sf::RectangleShape shape;
    int value;
};

struct elem2
{
    int shape;
    int value;
};

struct button //структура кнопки
{
    sf::RectangleShape body;
    sf::Text text;
};

enum sortt {bubble_sort_en, selection_sort_en, insertion_sort_en, quick_sort_en, merge_sort_en, heap_sort_en, counting_sort_en};
struct radio_button //структура radio button
{
    sf::CircleShape background;
    sf::CircleShape foreground;
    sf::Text text;
    bool checked = false;
    sortt sort_type;
};

void generate_array(elem arr[], int length, float elem_width, float height_one, sf::RenderWindow &w); //генерация массива
void draw_array(elem arr[], int length, sf::RenderWindow &w); //отрисовка массива
void swap_elements (elem a[], int index_1, int index_2); //перестановка двух элементов массива местами
void selection_sort (elem a[], int size); //сортировка выбором
void insertion_sort(elem arr[], int size); //сортировка вставками
int partition (elem arr[], int low, int high); //деление для быстрой сортировки
void quick_sort(elem arr[], int low, int high); //быстрая сортировка
int merge (elem a[], int p, int q, int r); //слияние для сортировки слиянием
void merge_sort (elem a[], int p, int r); //сортировка слиянием
bool mouse_on_button (sf::Mouse m, sf::RenderWindow &w, button b); //расположена ли мышь на кнопке
void init_button (button &b, float pos_x, float pos_y, sf::Color b_color, string text, sf::Font &font, sf::Color t_color, float t_size, sf::RenderWindow &w); //инициализация кнопки
void color_button (button &b, sf::Color b_color, sf::Color t_color); //изменение кнопки при наведении
void init_radio_button (radio_button &rb, float pos_x, float pos_y, sf::Color b_color, string text, sf::Font &font, sf::Color t_color, float t_size, sf::RenderWindow &w, sortt type); //инициализация radio button
bool mouse_on_radio_button (sf::Mouse m, sf::RenderWindow &w, radio_button rb); //расположена ли мышь на radio button
void bubble_sort (elem a[], int size); //сортировка пузырьком (обменом)
int parent (int i); //номер родителя (для обработки бинарного дерева)
int left (int i); //номер левого дочернего элемента (для обработки бинарного дерева)
int right (int i); //номер правого дочернего элемента (для обработки бинарного дерева)
void max_heapify (elem a[], int i, int heap_size); //поддержка свойств бинарного дерева
void build_max_heap (elem a[], int length, int &heap_size); //построение бинарного дерева
void heap_sort (elem a[], int length, int heap_size); //сортировка с помощью кучи (пирамидальная сортировка)
void counting_sort (elem b[], elem a[], int k, int length); //сортировка подсчётом

#endif /* funcs_hpp */
