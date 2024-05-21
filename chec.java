import com.mathsystem.api.graph.model.Graph;
import com.mathsystem.domain.graph.repository.Color;
import com.mathsystem.domain.graph.repository.GraphType;
import com.mathsystem.domain.plugin.plugintype.GraphProperty;

import com.mathsystem.api.graph.model.Edge;

import java.util.*;

import com.mathsystem.api.graph.model.Vertex;

public class CheckDivSet implements GraphProperty {

    public class ColorNode
    {
        public int color = 0;
        public Vertex node;
        public ColorNode(Vertex node) {
            this.node = node;
        }
    }

    public ColorNode getColorNode(UUID edge, Vector<ColorNode> set_color_node)
    {
        for (ColorNode temp_color : set_color_node) {
            if (temp_color.node.getId().equals(edge)) {
                return temp_color;
            }
        }
        return null;
    }

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

    @Override
    public boolean execute(Graph graph) {
        int start_count_components = getComponent(graph);
        HashSet<UUID> delVertexes = getDelVertexes(graph);
        if (delVertexes.isEmpty() || graph.getDirectType() == GraphType.DIRECTED) {
            return false;
        }
        sliceGraph(delVertexes, graph);
        int end_count_components = getComponent(graph);
        return end_count_components > start_count_components;
    }


}
