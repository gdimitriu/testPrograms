package io.github.gdimitriu.saxon.old;
import net.sf.saxon.expr.XPathContext;
import net.sf.saxon.om.AttributeCollection;
import net.sf.saxon.om.Item;
import net.sf.saxon.om.NodeInfo;
import net.sf.saxon.pull.PullProvider;
import net.sf.saxon.style.StyleElement;
import net.sf.saxon.tinytree.TinyNodeImpl;
import net.sf.saxon.tinytree.TinyTreeWalker;
import net.sf.saxon.trace.InstructionInfo;
import net.sf.saxon.trace.TraceListener;
import net.sf.saxon.trans.XPathException;

import java.util.HashMap;
import java.util.Map;

public class MyOldTraceListener implements TraceListener {
    public MyOldTraceListener() {
    }
    @Override
    public void open() {

    }

    @Override
    public void close() {

    }

    @Override
    public void enter(InstructionInfo instructionInfo, XPathContext xPathContext) {
        if (instructionInfo instanceof StyleElement) {
            StyleElement element = (StyleElement) instructionInfo;
            String name = element.getDisplayName();
            int line = element.getLineNumber();

            Map<String,String> attributes = new HashMap<>();
            // extract attributes
            AttributeCollection ac = element.getAttributeList();
            for (int j = 0; j < ac.getLength(); j++) {
                attributes.put(ac.getQName(j),ac.getValue(j));
            }

            String rez = String.format("<<-->> [%d]: %s %s %s",line,name,element.getSystemId(),attributes);
            System.out.println(rez);
        }
    }

    @Override
    public void leave(InstructionInfo instructionInfo) {
    }

    @Override
    public void startCurrentItem(Item item) {
        if (item instanceof NodeInfo) {
            NodeInfo inf = (NodeInfo) item;
            Map<String,String> attributes = new HashMap<>();

            if (inf.getLineNumber() > 0) {
                // extract attributes
                TinyTreeWalker ttw = new TinyTreeWalker((TinyNodeImpl) inf);
                try {
                    if (ttw.next() == PullProvider.START_ELEMENT) {
                        AttributeCollection ac = ttw.getAttributes();
                        for (int j = 0; j < ac.getLength(); j++) {
                            attributes.put(ac.getQName(j), ac.getValue(j));
                        }
                    }
                } catch (XPathException e) {
                    e.printStackTrace();
                } finally {
                    ttw.close();
                }

                String rez = String.format("-->> [%d]: %s %s %s",inf.getLineNumber(),inf.getDisplayName(),inf.getSystemId(),attributes);
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
}
