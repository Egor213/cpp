import com.mathsystem.api.graph.model.Graph;
import com.mathsystem.domain.graph.repository.Color;
import com.mathsystem.domain.graph.repository.GraphType;
import com.mathsystem.domain.plugin.plugintype.GraphProperty;

import com.mathsystem.api.graph.model.Edge;

import java.util.Set;
import java.util.UUID;
import com.mathsystem.api.graph.model.Vertex;
import java.util.Map;
import java.util.HashSet;
import java.util.Iterator;
public class CheckDivSet implements GraphProperty {

    Set<UUID> visited = new HashSet<>();

    public void dfs(UUID node, Graph graph)
    {
        if (!visited.contains(node)) {
            visited.add(node);
            for (Edge per : graph.getEdges())
            {
                if (graph.getDirectType() == GraphType.DIRECTED)
                {
                    if (per.getFromV().equals(node))
                    {
                        dfs(per.getToV(), graph);
                    }
                }
                else
                {
                    if (per.getFromV().equals(node))
                    {
                        dfs(per.getToV(), graph);
                    }
                    else if(per.getToV().equals(node))
                    {
                        dfs(per.getFromV(), graph);
                    }
                }

            }
        }
    }


    @Override
    public boolean execute(Graph graph) {
        HashSet<UUID> delVertices = new HashSet<>();

        Iterator<Map.Entry<UUID, Vertex>> iterator = graph.getVertices().entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry<UUID, Vertex> entry = iterator.next();
            if (entry.getValue().getColor() == Color.red) {
                delVertices.add(entry.getKey());
                iterator.remove();
            }
        }

        if (delVertices.isEmpty())
        {
            return false;
        }

        Iterator<Edge> iterator2 = graph.getEdges().iterator();
        while (iterator2.hasNext()) {
            Edge edge = iterator2.next();
            if (delVertices.contains(edge.getToV()) || delVertices.contains(edge.getFromV())) {
                iterator2.remove();
            }
        }



        for (UUID id : graph.getVertices().keySet())
        {
            visited.clear();
            dfs(id, graph);
            Set<UUID> copySet = new HashSet<>(visited);
            if (visited.size() != graph.getVertices().size())
            {
                for (UUID id2 : graph.getVertices().keySet())
                {
                    if (!copySet.contains(id2))
                    {
                        visited.clear();
                        dfs(id2, graph);
                        if (!visited.contains(id))
                        {
                            return true;
                        }
                    }

                }
            }
        }
        return false;
    }


}
