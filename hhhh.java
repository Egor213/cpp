import com.mathsystem.api.graph.model.Graph;
import com.mathsystem.domain.graph.repository.Color;
import com.mathsystem.domain.graph.repository.GraphType;
import com.mathsystem.domain.plugin.plugintype.GraphProperty;

import com.mathsystem.api.graph.model.Edge;

import java.util.*;

import com.mathsystem.api.graph.model.Vertex;

public class CheckDivSet implements GraphProperty {

    Set<UUID> visited = new HashSet<>();

//    public void dfs(UUID node, Graph graph)
//    {
//        if (!visited.contains(node)) {
//            visited.add(node);
//            for (Edge per : graph.getEdges())
//            {
//                if (graph.getDirectType() == GraphType.DIRECTED)
//                {
//                    if (per.getFromV().equals(node))
//                    {
//                        dfs(per.getToV(), graph);
//                    }
//                }
//                else
//                {
//                    if (per.getFromV().equals(node))
//                    {
//                        dfs(per.getToV(), graph);
//                    }
//                    else if(per.getToV().equals(node))
//                    {
//                        dfs(per.getFromV(), graph);
//                    }
//                }
//
//            }
//        }
//    }

    public class Node
    {
        public Color color;
        public UUID id;
        public int color_task = 0;
        public Node(UUID id, Color color)
        {
            this.id = id;
            this.color = color;
        }
    }

    public Color getColor(UUID node, Graph graph)
    {
        for (Map.Entry<UUID, Vertex> entry : graph.getVertices().entrySet())
        {
            if (entry.getKey().equals(node))
            {
                return entry.getValue().getColor();
            }
        }
        return Color.gray;
    }

    public boolean checkConteins(Node node, Map<Node, Vector<Node>> map_graph)
    {
        for (Map.Entry<Node, Vector<Node>> entry : map_graph.entrySet()) {
            UUID key = entry.getKey().id;
            if (key.equals(node.id))
                return true;
        }
        return false;
    }

    public Map<Node, Vector<Node>> createMap(Graph graph)
    {
        Map<Node, Vector<Node>> map_graph = new HashMap<>();
        for (Edge per : graph.getEdges())
        {
            System.out.println(per);
        }

        for (Map.Entry<UUID, Vertex> entry : graph.getVertices().entrySet())
        {
            UUID key = entry.getKey();
            Vertex value = entry.getValue();
            System.out.println("Key: " + key + ", Value: " + value);
        }


        for (Edge per : graph.getEdges())
        {
            if (graph.getDirectType() == GraphType.DIRECTED)
            {
                Color a = getColor(per.getToV(), graph);
                Node node_from = new Node(per.getFromV(), getColor(per.getFromV(), graph));
                Node node_to = new Node(per.getToV(), getColor(per.getToV(), graph));
                if (checkConteins(node_from, map_graph))
                {
                    Vector<Node> vector = map_graph.get(node_from);
                    vector.add(node_to);
                }
                else
                {
                    // Если node_from отсутствует в качестве ключа, создаем новый список и добавляем node_to в него
                    Vector<Node> newList = new Vector<>();
                    newList.add(node_to);
                    map_graph.put(node_from, newList);
                }
            }
        }
        for (Map.Entry<UUID, Vertex> entry : graph.getVertices().entrySet())
        {
            UUID key = entry.getKey();
            Vertex value = entry.getValue();
            Node node = new Node(key, getColor(key, graph));
            if (!checkConteins(node, map_graph))
            {
                Vector<Node> newList = new Vector<>();
                map_graph.put(node, newList);
            }
        }
        for (Map.Entry<Node, Vector<Node>> entry : map_graph.entrySet()) {
            UUID key = entry.getKey().id;
            Color color = entry.getKey().color;
            Vector<Node> value = entry.getValue();
            System.out.print("Key: " + key + ", Color: " + color + ", Value: ");
            for (Node a : value)
            {
                System.out.print(a.id + ", ");
            }
            System.out.println();
        }
        return map_graph;
    }


    @Override
    public boolean execute(Graph graph) {

        Map<Node, Vector<Node>> a = createMap(graph);
        //  Надо посчитать количество компонент связности изнчально + после удаления


//        HashSet<UUID> delVertices = new HashSet<>();
//
//        Iterator<Map.Entry<UUID, Vertex>> iterator = graph.getVertices().entrySet().iterator();
//        while (iterator.hasNext()) {
//            Map.Entry<UUID, Vertex> entry = iterator.next();
//            if (entry.getValue().getColor() == Color.red) {
//                delVertices.add(entry.getKey());
//                iterator.remove();
//            }
//        }
//
//        if (delVertices.isEmpty())
//        {
//            return false;
//        }
//
//        Iterator<Edge> iterator2 = graph.getEdges().iterator();
//        while (iterator2.hasNext()) {
//            Edge edge = iterator2.next();
//            if (delVertices.contains(edge.getToV()) || delVertices.contains(edge.getFromV())) {
//                iterator2.remove();
//            }
//        }
//
//
//
//        for (UUID id : graph.getVertices().keySet())
//        {
//            visited.clear();
//            dfs(id, graph);
//            Set<UUID> copySet = new HashSet<>(visited);
//            if (visited.size() != graph.getVertices().size())
//            {
//                for (UUID id2 : graph.getVertices().keySet())
//                {
//                    if (!copySet.contains(id2))
//                    {
//                        visited.clear();
//                        dfs(id2, graph);
//                        if (!visited.contains(id))
//                        {
//                            return true;
//                        }
//                    }
//
//                }
//            }
//        }
        return false;
    }


}
