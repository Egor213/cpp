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

    HashSet<Integer> unic_set;
    public void dfs(ColorNode color_node, Graph graph, int number_color, Vector<ColorNode> set_color_node, boolean with_red_node)
    {
        if (color_node.color == 0) {
            if (with_red_node && color_node.node.getColor() == Color.red)
            {
                return;
            }
            color_node.color = number_color;
            for (Edge edge : graph.getEdges()) {
                if (edge.getFromV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getToV(), set_color_node);
                    dfs(temp_color, graph, number_color, set_color_node, with_red_node);
                }
                else if (edge.getToV().equals(color_node.node.getId())) {
                    ColorNode temp_color = getColorNode(edge.getFromV(), set_color_node);
                    dfs(temp_color, graph, number_color, set_color_node, with_red_node);
                }
            }
        }
    }

    public int getComponent(Graph graph, boolean with_red_node)
    {
        Vector<ColorNode> set_color_nodes = new Vector<>();
        int number_color = 0;
        for (Vertex ver : graph.getVertices().values()) {
            ColorNode temp = new ColorNode(ver);
            set_color_nodes.add(temp);
        }
        for (ColorNode node : set_color_nodes) {
            if (node.color == 0) {
                if (with_red_node && node.node.getColor() == Color.red)
                {
                    continue;
                }
                number_color = number_color + 1;
                dfs(node, graph, number_color, set_color_nodes, with_red_node);
            }
        }
        return number_color;
    }

    @Override
    public boolean execute(Graph graph) {
       // int start_count_components = getComponent(graph, false);
        int end_count_components = getComponent(graph, true);

        //return end_count_components > start_count_components;
    }


}
