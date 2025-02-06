/**
    Copyright (c) 2018 Gabriel Dimitriu All rights reserved.
	DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This file is part of poc_datastore project.

    poc_datanucleus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    poc_datanucleus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with poc_datastore.  If not, see <http://www.gnu.org/licenses/>.
 */
package poc_datastore.cassandra.basic.test;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

import com.datastax.driver.core.ResultSet;
import com.datastax.driver.core.Row;
import com.datastax.driver.core.Statement;
import com.datastax.driver.core.querybuilder.QueryBuilder;
import com.datastax.driver.extras.codecs.json.JacksonJsonCodec;

import poc_datastore.pocelement.PocElement;

/**
 * @author Gabriel Dimitriu
 *
 */
public class BaseOperationTests extends BaseTestOperations {


	/**
	 * - create a connection
	 * - create keyspace
	 * - use keyspace
	 * - delete keyspace
	 */
	@Test
	public void createConnectionAndDeleteKsyspace() {

		session.execute("DROP KEYSPACE poc_datastore");
		// close the session
		session.close();
	}

	/**
	 * - create table
	 * - execute select
	 * - validate that the columns exist
	 */
	@Test
	public void createTablePoc() {
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_name");
		columns.add("poc_value");
		// Query
		String query = "CREATE TABLE poc(poc_id int PRIMARY KEY, " + "poc_name text, " + "poc_value text" + ");";
		session.execute(query);
		Statement statement = QueryBuilder.select().from("poc");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
	}
	
	@Test
	public void insertIntoTablePoc() {
		createTablePoc();
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_name");
		columns.add("poc_value");
		List<Object> values = new ArrayList<>();
		values.add(new Integer(1));
		values.add("name1");
		values.add("value1");
		Statement insert = QueryBuilder.insertInto("poc").values(columns, values);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("poc");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			for (int i = 0; i < values.size(); i++) {
				assertEquals(values.get(i), rez.getObject(i));
			}
		}
	}
	
	@Test
	public void insertIntoTablePocJSON() {
		createTablePoc();
		cluster.getConfiguration().getCodecRegistry().register(new JacksonJsonCodec<PocElement>(PocElement.class));
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_name");
		columns.add("poc_value");
		List<Object> values = new ArrayList<>();
		values.add(new Integer(1));
		values.add("name1");
		values.add("value1");
		PocElement json = new PocElement(1,"name1", "value1");
		Statement insert = QueryBuilder.insertInto("poc").json(json);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("poc");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			for (int i = 0; i < values.size(); i++) {
				assertEquals(values.get(i), rez.getObject(i));
			}
		}
	}
}
