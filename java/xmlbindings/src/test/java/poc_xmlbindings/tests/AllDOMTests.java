package poc_xmlbindings.tests;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

@RunWith(Suite.class)
@SuiteClasses({poc_xmlbindings.tests.jdom.ExploreTest.class,
	poc_xmlbindings.tests.w3cdom.ExploreTest.class,
	poc_xmlbindings.tests.xom.ExploreTest.class})
public class AllDOMTests {

}
