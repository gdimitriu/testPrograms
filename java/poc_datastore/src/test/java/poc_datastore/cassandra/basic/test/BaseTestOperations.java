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

import org.junit.After;
import org.junit.Before;

import com.datastax.driver.core.Cluster;
import com.datastax.driver.core.Session;

/**
 * @author Gabriel Dimitriu
 *
 */
public abstract class BaseTestOperations {

	protected Session session = null;
	
	protected Cluster cluster = null;
	
	@After
	public void afterTest() {
		if (session == null || session.isClosed()) {
			session = Cluster.builder().addContactPoint("127.0.0.1").build().connect();
		}
		session.execute("DROP KEYSPACE IF EXISTS poc_datastore");
		session.close();
		session = null;
	}
	
	@Before
	public void beforeTest() {
		session = createAndUseKeyspace();
	}

	/**
	 * - create the connection - create the keyspace - use keyspace
	 * 
	 * @return the session from cassandra
	 */
	public Session createAndUseKeyspace() {
		if (cluster == null) {
			// create the cluster for cassandra
			cluster = Cluster.builder().addContactPoint("127.0.0.1").build();
		}
		// create the session
		Session session = cluster.connect();
		
		session.execute("DROP KEYSPACE IF EXISTS poc_datastore");

		// Query to create the keyspace
		String query = "CREATE KEYSPACE poc_datastore WITH replication "
				+ "= {'class':'SimpleStrategy', 'replication_factor':1};";

		// Executing the query
		session.execute(query);
		// use the keyspace
		query = "USE poc_datastore;";
		session.execute(query);
		return session;
	}

}
