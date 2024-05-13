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
*Выделенное множество - вершины графа красного цвета.* <br>
1. Для начала необходимо узнать изначальное количество компонент связности, так как не гарантируется, что изначальный граф содержит одну компонент связности.<br>
2. Для нахождения количества компонент связности графа был создан специальный класс *ColorNode* который фактически является расширение уже созданного класса Vertex. Данный класс необходим для более комфортной работы по нахождению компонент связности. Поле *color* отвечается за номер цвета, который относится к некоторой компонент связности.
```Java 
  public class ColorNode
    {
        public int color = 0;
        public Vertex node;
        public ColorNode(Vertex node) {
            this.node = node;
        }
    }
```
3. Для нахождения количества компонент связности реализован метод *getComponent*. 
```Java
public int getComponent(Graph graph)
    {
        Vector<ColorNode> set_color_nodes = new Vector<>();
        int number_color = 0;
        for (Vertex ver : graph.getVertices().values()) {
            ColorNode temp = new ColorNode(ver);
            set_color_nodes.add(temp);
        }
        for (ColorNode node : set_color_nodes) {
            if (node.color == 0) {
                number_color = number_color + 1;
                dfs(node, graph, number_color, set_color_nodes);
            }
        }
        return number_color;
    }
```
В первую очередь в данном методе строится множество *ColorNode* посредством прохода по имеющимся вершинам. После этого запускаем цикл, в котором совершаем проход по всем *ColorNode's* (т.е. по всем вершинам графа). В начале проверяем, покрашена ли данная вершина, если вершина еще не обрабатывалась, то увеличиваем значение цвета и запускаем поиск в глубину по графу. С помощью данного обхода мы помечаем все встретившиеся вершины от запущенной, таким образом отделяя одну компонент связности от других.
```Java
public void dfs(ColorNode color_node, Graph graph, int number_color, Vector<ColorNode> set_color_node)
    {
        if (color_node.color == 0) {
            color_node.color = number_color;
            for (Edge edge : graph.getEdges()) {
                if (edge.getFromV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                    dfs(temp_color, graph, number_color, set_color_node);
                }
                else if (edge.getToV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getFromV(), set_color_node);
                    dfs(temp_color, graph, number_color, set_color_node);
                }
            }
        }
    }
```
4. После нахождения всех компонент связности выделяется множество вершин, которые необходимо удалить. Для этого используется метод *getDelVertexes*. С помощью простого цикла мы перебираем все вершины графа и добавляем в список *delVertexes* только те, которые окрашены в красный цвет.
```Java
public HashSet<UUID> getDelVertexes(Graph graph)
    {
        HashSet<UUID> delVertexes = new HashSet<>();
        Iterator<Map.Entry<UUID, Vertex>> iterator = graph.getVertices().entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry<UUID, Vertex> entry = iterator.next();
            if (entry.getValue().getColor() == Color.red) {
                delVertexes.add(entry.getKey());
                iterator.remove();
            }
        }
        return delVertexes;
    }
```
5. После получения множества вершин помеченных вершин, мы удаляем их из графа с помощью метода *sliceGraph*
```Java
public void sliceGraph(HashSet<UUID> delVertexes, Graph graph)
    {
        Iterator<Edge> iterator = graph.getEdges().iterator();
        while (iterator.hasNext()) {
            Edge edge = iterator.next();
            if (delVertexes.contains(edge.getToV()) || delVertexes.contains(edge.getFromV())) {
                iterator.remove();
            }
        }
    }
```
  6. После удаления вершин, мы вновь проверяем количество компонент связности.
  7. Сравниваем количество компонент связности в изначальном графе и в графе, который получился после удаления вершин. Если количество компонент связности увеличилось, значит множество являлось разделяюшим. <br>
## *Примечания:*
1. *Если подать граф без помеченных вершин - false, если нет множества, то оно не является разделяющим. Таким же образом граф без любых вершин.*
2. *Если подать ориентированный граф - false.*
3. *Если весь граф это выделенное множество - false, так как компонент связности не остается.*
