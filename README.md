# Разделяющие множества

## Определение
Пусть _X, Y ⊂ V (G), R ⊂ V (G) ∪ E(G)_.
1) Назовем множество R разделяющим, если граф G − R несвязен.
2) Пусть _X ⊄ R, Y ⊄ R_. Будем говорить, что R разделяет множества X и Y (или, что то же самое, отделяет множества X и Y друг от
друга), если никакие две вершины _v<sub>x</sub> ∈ X_ и _v<sub>y</sub> ∈ Y_ не лежат в одной
компоненте связности графа G − R

## Пример
![img1.png](pictures%2Fimg1.png) <br>
*Красные вершины являются разделяющим множеством данного графа. После их удаления граф распадается на 6 компонент связности, хотя изначально компонента была одна*

## Алгоритм
*Данный модуль работает только на неориентированных графах.* <br>
В первую очередь необходимо узнать изначальное количество компонент связности, так как не гарантируется, что изначальный граф содержит одну компонент связности.<br>
Для нахождения количества компонент связности графа был создан специальный класс *ColorNode* который фактически является расширение уже созданного класса Vertex.
