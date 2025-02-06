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

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.Test;

import com.datastax.driver.core.Cluster;
import com.datastax.driver.core.CodecRegistry;
import com.datastax.driver.core.ResultSet;
import com.datastax.driver.core.Row;
import com.datastax.driver.core.Statement;
import com.datastax.driver.core.TypeCodec;
import com.datastax.driver.core.UDTValue;
import com.datastax.driver.core.UserType;
import com.datastax.driver.core.querybuilder.QueryBuilder;
import com.datastax.driver.extras.codecs.json.JacksonJsonCodec;

import poc_datastore.address.Address;
import poc_datastore.cassandra.AddressCodec;
import poc_datastore.cassandra.JsonCodec;
import poc_datastore.pocelement.PocElementBase;

/**
 * @author Gabriel Dimitriu
 *
 */
public class CodecOperationsTests extends BaseTestOperations {

	/**
	 * - create table
	 * - execute select
	 * - validate that the columns exist
	 */
	private void createTableCodec() {
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		// Query
		String query = "CREATE TABLE codec(poc_id int PRIMARY KEY, " + "poc_json text" + ");";
		session.execute(query);
		Statement statement = QueryBuilder.select().from("codec");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
	}
	
	/**
	 * - create table
	 * - execute select
	 * - validate that the columns exist
	 */
	private void createListTableCodec() {
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		// Query
		String query = "CREATE TABLE codec_list(poc_id int PRIMARY KEY, " + "poc_json list<text>" + ");";
		session.execute(query);
		Statement statement = QueryBuilder.select().from("codec_list");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
	}
	
	/**
	 * - create table
	 * - execute select
	 * - validate that the columns exist
	 */
	private void createMapTableCodec() {
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		// Query
		String query = "CREATE TABLE codec_map(poc_id int PRIMARY KEY, " + "poc_json map<text, text>" + ");";
		session.execute(query);
		Statement statement = QueryBuilder.select().from("codec_map");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
	}
	
	@Test
	public void insertIntoTableCodecAPOJO() {
		createTableCodec();
		cluster.getConfiguration().getCodecRegistry().register(new JacksonJsonCodec<PocElementBase>(PocElementBase.class));
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		PocElementBase json = new PocElementBase("name1", "value1");
		Statement insert = QueryBuilder.insertInto("codec").value("poc_id",1).value("poc_json", json);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("codec");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			PocElementBase elem = rez.get(1, PocElementBase.class);
			assertEquals(json, elem);
		}
	}
	
	@Test
	public void insertIntoTableListCodecAPOJO() {
		createListTableCodec();
		cluster.getConfiguration().getCodecRegistry().register(new JacksonJsonCodec<PocElementBase>(PocElementBase.class));
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		List<PocElementBase> jsonList = new ArrayList<>();
		jsonList.add(new PocElementBase("name1", "value1"));
		jsonList.add(new PocElementBase("name2", "value2"));
		Statement insert = QueryBuilder.insertInto("codec_list").value("poc_id",1).value("poc_json", jsonList);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("codec_list");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			List<PocElementBase> elems = rez.getList(1, PocElementBase.class);
			assertEquals(jsonList.size(), elems.size());
			for (int i = 0; i < elems.size(); i++) {
				assertEquals(jsonList.get(i), elems.get(i));
			}
		}
	}
	
	@Test
	public void insertIntoTableMapCodecAPOJO() {
		createMapTableCodec();
		cluster.getConfiguration().getCodecRegistry().register(new JacksonJsonCodec<PocElementBase>(PocElementBase.class));
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		Map<String, PocElementBase> jsonMap = new HashMap<>();
		jsonMap.put("key1",new PocElementBase("name1", "value1"));
		jsonMap.put("key2", new PocElementBase("name2", "value2"));
		Statement insert = QueryBuilder.insertInto("codec_map").value("poc_id",1).value("poc_json", jsonMap);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("codec_map");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			Map<String, PocElementBase> elems = rez.getMap(1, String.class, PocElementBase.class);
			assertEquals(jsonMap.size(), elems.size());
			assertEquals(jsonMap.get("key1"), elems.get("key1"));
			assertEquals(jsonMap.get("key2"), elems.get("key2"));
		}
	}

	@Test
	public void insertIntoTableMapCustomCodecAPOJO() {
		createMapTableCodec();
		cluster.getConfiguration().getCodecRegistry().register(new JsonCodec<PocElementBase>(PocElementBase.class));
		List<String> columns = new ArrayList<>();
		columns.add("poc_id");
		columns.add("poc_json");
		Map<String, PocElementBase> jsonMap = new HashMap<>();
		jsonMap.put("key1",new PocElementBase("name1", "value1"));
		jsonMap.put("key2", new PocElementBase("name2", "value2"));
		Statement insert = QueryBuilder.insertInto("codec_map").value("poc_id",1).value("poc_json", jsonMap);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("codec_map");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			Map<String, PocElementBase> elems = rez.getMap(1, String.class, PocElementBase.class);
			assertEquals(jsonMap.size(), elems.size());
			assertEquals(jsonMap.get("key1"), elems.get("key1"));
			assertEquals(jsonMap.get("key2"), elems.get("key2"));
		}
	}
	
	/**
	 * - create custom type name address
	 * - create table users using address
	 * - execute select
	 * - validate that the columns exist
	 */
	private void createCustomTypeTableCodec() {
		List<String> columns = new ArrayList<>();
		columns.add("id");
		columns.add("addresses");
		String createType = "CREATE TYPE address(city varchar, street varchar);";
		session.execute(createType);
		// Query
		String query = "CREATE TABLE users(id int PRIMARY KEY, " + "addresses frozen<address>" + ");";
		session.execute(query);
		Statement statement = QueryBuilder.select().from("users");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
	}
	
	@Test
	public void insertCustomTypeIntoTableUsingCustomCodec() {
		// only if you do not intend to use CodecRegistry.DEFAULT_INSTANCE
		CodecRegistry codecRegistry = new CodecRegistry();
		cluster = Cluster.builder()
				    .addContactPoints("127.0.0.1")
				    .withCodecRegistry(codecRegistry)
				    .build();
		session = createAndUseKeyspace();
		createCustomTypeTableCodec();
		UserType addressType = cluster.getMetadata().getKeyspace("poc_datastore").getUserType("address");
		TypeCodec<UDTValue> addressTypeCodec = codecRegistry.codecFor(addressType);
		AddressCodec addressCodec = new AddressCodec(addressTypeCodec, Address.class);
		codecRegistry.register(addressCodec);
		List<String> columns = new ArrayList<>();
		columns.add("id");
		columns.add("addresses");
		Address add = new Address("buc", "niet");
		Statement insert = QueryBuilder.insertInto("users").value("id",1).value("addresses", add);
		session.execute(insert);
		Statement statement = QueryBuilder.select().from("users");
		ResultSet rezult = session.execute(statement);
		for (String column : columns) {
			assertTrue(rezult.getColumnDefinitions().contains(column));
		}
		for ( Row rez : rezult) {
			Address elem = rez.get(1, Address.class);
			assertEquals(add, elem);
		}
	}
}
