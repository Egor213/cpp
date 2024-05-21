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

    public void workNode(Graph graph, ColorNode color_node, Vector<ColorNode> set_color_node, boolean with_red_node, int number_color){
        for (Edge edge : graph.getEdges()) {
            if (edge.getFromV().equals(color_node.node.getId())) {
                ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                dfsUndirection(temp_color, graph, number_color, set_color_node, with_red_node);
            }
            else if (edge.getToV().equals(color_node.node.getId())) {
                ColorNode temp_color = getColorNode(edge.getFromV(), set_color_node);
                dfsUndirection(temp_color, graph, number_color, set_color_node, with_red_node);
            }
        }
    }

    HashSet<Integer> unic_set = new HashSet<>();
    HashSet<ColorNode> visited = new HashSet<>();
    Vector<ColorNode> set_color_nodes = new Vector<>();
    public void dfsUndirection(ColorNode color_node, Graph graph, int number_color, Vector<ColorNode> set_color_node, boolean with_red_node)
    {
        if (with_red_node) {
            if (color_node.color == 0 && color_node.node.getColor() != Color.red) {
                color_node.color = number_color;
                workNode(graph, color_node, set_color_node, with_red_node, number_color);
            }
        }
        else {
            if (!visited.contains(color_node)) {
                visited.add(color_node);
                unic_set.add(color_node.color);
                workNode(graph, color_node, set_color_node, with_red_node, number_color);
            }
        }
    }

    public boolean solveUndirection(Graph graph, boolean with_red_node)
    {
        int number_color = 0;
        if (with_red_node) {
            for (Vertex ver : graph.getVertices().values()) {
                ColorNode temp = new ColorNode(ver);
                set_color_nodes.add(temp);
            }
        }
        for (ColorNode node : set_color_nodes) {
            if (with_red_node) {
                if (node.color == 0 && node.node.getColor() != Color.red) {
                    number_color = number_color + 1;
                    dfsUndirection(node, graph, number_color, set_color_nodes, with_red_node);
                }
            }
            else {
                if (!visited.contains(node)) {
                    dfsUndirection(node, graph, number_color, set_color_nodes, with_red_node);
                    if (unic_set.size() > 2){
                        return true;
                    }
                    unic_set.clear();
                }
            }
        }
        return false;
    }


    //ДАЛЬШЕ ДЛЯ ОРИЕНТИРОВАННОГО ГРАФА
    public Edge getCopyEdgeReverse(Edge edge)
    {
        Edge reverse_edge = new Edge();
        reverse_edge.setToV(edge.getFromV());
        reverse_edge.setFromV(edge.getToV());
        reverse_edge.setColor(edge.getColor());
        reverse_edge.setWeight(edge.getWeight());
        reverse_edge.setLabel(edge.getLabel());
        return reverse_edge;
    }

    public List<Edge> getReverseEdges(Graph graph){
        List<Edge> temp = new ArrayList<>();
        for (Edge edge : graph.getEdges()) {
            Edge reverse_edge =getCopyEdgeReverse(edge);
            temp.add(reverse_edge);
        }
        return temp;
    }

    Vector<ColorNode> save_time_quit = new Vector<>();
    public void dfsSetTimeQuit(ColorNode color_node, List<Edge> reverse_edges, Vector<ColorNode> set_color_node, boolean with_red) {
        if (!visited.contains(color_node)) {
            if (!with_red) {
                if (color_node.node.getColor() == Color.red) {
                    return;
                }
            }
            visited.add(color_node);
            for (Edge edge : reverse_edges) {
                if (edge.getFromV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                    dfsSetTimeQuit(temp_color, reverse_edges, set_color_node, with_red);
                }
            }
            save_time_quit.add(color_node);
        }
    }

    public void componentDfsNoRed(Graph graph, Vector<ColorNode> set_color_node, ColorNode color_node, int color_number) {
        if (color_node.color == 0 && color_node.node.getColor() != Color.red) {
            color_node.color = color_number;
            for (Edge edge : graph.getEdges()) {
                if (edge.getFromV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                    componentDfsNoRed(graph, set_color_nodes, temp_color, color_number);
                }
            }
        }
    }

    public void setColorNodes(Graph graph) {
        for (Vertex ver : graph.getVertices().values()) {
            ColorNode temp = new ColorNode(ver);
            set_color_nodes.add(temp);
        }
    }

    public void checkDfsDirectional(Graph graph, Vector<ColorNode> set_color_node, ColorNode color_node) {
        if (!visited.contains(color_node)) {
            visited.add(color_node);
            unic_set.add(color_node.color);
            for (Edge edge : graph.getEdges()) {
                if (edge.getFromV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                    checkDfsDirectional(graph, set_color_node, temp_color);
                }
            }
        }
    }

    public boolean solve_direction(Graph graph, List<Edge> reverse_edges) {
        setColorNodes(graph);
        for (ColorNode color_node : set_color_nodes) {
            dfsSetTimeQuit(color_node, reverse_edges, set_color_nodes, false);
        }

        int color_number = 0;
        for (int i = save_time_quit.size() - 1; i >= 0; i--) {
            ColorNode node = save_time_quit.get(i);
            if (node.color == 0) {
                color_number++;
                componentDfsNoRed(graph, set_color_nodes, node, color_number);
            }
        }
        for (ColorNode node : set_color_nodes) {
            System.out.println(node.node.getLabel() + " Color: " + node.color);
        }
        visited.clear();
        save_time_quit.clear();
        for (ColorNode color_node : set_color_nodes) {
            dfsSetTimeQuit(color_node, reverse_edges, set_color_nodes, true);
        }
        visited.clear();
        for (int i = save_time_quit.size() - 1; i >= 0; i--) {
            ColorNode node = save_time_quit.get(i);
            checkDfsDirectional(graph, set_color_nodes, node);
            if (unic_set.size() > 2){
                return true;
            }
            unic_set.clear();
        }

        for (ColorNode node : set_color_nodes) {
            System.out.println(node.node.getLabel() + " Color: " + node.color);
        }

        return false;

    }


    @Override
    public boolean execute(Graph graph) {
        if (graph.getDirectType() == GraphType.UNDIRECTED) {
            solveUndirection(graph, true);
            return solveUndirection(graph, false);
        }
        else {
            List<Edge> reverse_edges = getReverseEdges(graph);
            return solve_direction(graph, reverse_edges);
        }
    }


}
