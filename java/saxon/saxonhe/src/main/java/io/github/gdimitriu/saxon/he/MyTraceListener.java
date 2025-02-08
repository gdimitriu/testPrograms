package io.github.gdimitriu.saxon.he;

import net.sf.saxon.Controller;
import net.sf.saxon.expr.Expression;
import net.sf.saxon.expr.XPathContext;
import net.sf.saxon.functions.Trace;
import net.sf.saxon.lib.Logger;
import net.sf.saxon.lib.TraceListener;
import net.sf.saxon.om.AttributeMap;
import net.sf.saxon.om.Item;
import net.sf.saxon.om.NodeInfo;
import net.sf.saxon.trace.Traceable;
import net.sf.saxon.trans.Mode;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MyTraceListener implements TraceListener {
    public MyTraceListener() {
    }

    @Override
    public void setOutputDestination(Logger logger) {

    }

    @Override
    public void open(Controller controller) {

    }

    @Override
    public void close() {

    }

    @Override
    public void enter(Traceable instructionInfo, Map<String, Object> properties, XPathContext context) {
        TraceListener.super.enter(instructionInfo, properties, context);
        if (instructionInfo instanceof Expression) {
            Expression expression = (Expression)instructionInfo;
            String expressionName = expression.getExpressionName();
            List<String> tmp = new ArrayList<>();
            System.out.println(expression);
            System.out.println(String.format("<<---->> %d %s %s %s", instructionInfo.getLocation().getLineNumber(),expressionName, properties,tmp));
        }
        if (instructionInfo instanceof Trace) {
            Trace expression = (Trace)instructionInfo;
            String expressionName = expression.getObjectName().getDisplayName();
            List<?> tmp = new ArrayList<>();
            System.out.println(String.format("<<--!!-->> %d %s %s %s", instructionInfo.getLocation().getLineNumber(),expressionName, properties,tmp));
        }

        if (instructionInfo != null && instructionInfo.getObjectName() != null) {
            String name = instructionInfo.getObjectName().getDisplayName();
            int line = instructionInfo.getLocation().getLineNumber();
            String systemId = instructionInfo.getLocation().getSystemId();
            String rez = String.format("<<-->> [%d]: %s %s %s", line, name, systemId, properties);
            System.out.println(rez);
        }
    }

    @Override
    public void leave(Traceable instruction) {
        TraceListener.super.leave(instruction);
    }

    @Override
    public void startCurrentItem(Item item) {
        System.out.println("item= " + item.getStringValue());
        if (item instanceof NodeInfo) {
            NodeInfo inf = (NodeInfo) item;
            AttributeMap attributes = null;

            if (inf.getLineNumber() > 0) {
                attributes = ((NodeInfo) item).attributes();
                String rez = String.format("-->> [%d]: %s %s %s",inf.getLineNumber(),inf.getDisplayName(),inf.getSystemId(),attributes.asList());
                System.out.println(rez);
            }
        }
    }

    @Override
    public void endCurrentItem(Item item) {
        if (item instanceof NodeInfo) {
            NodeInfo inf = (NodeInfo) item;
            if (inf.getLineNumber() > 0) {
                String rez = String.format("<<-- [%d]: %s %s",inf.getLineNumber(),inf.getDisplayName(),inf.getSystemId());
                System.out.println(rez);
            }
        }
    }

    @Override
    public void startRuleSearch() {
        TraceListener.super.startRuleSearch();
    }

    @Override
    public void endRuleSearch(Object rule, Mode mode, Item item) {
        TraceListener.super.endRuleSearch(rule, mode, item);
    }
}
