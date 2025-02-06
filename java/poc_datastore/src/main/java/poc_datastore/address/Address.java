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
package poc_datastore.address;

/**
 * @author Gabriel Dimitriu
 *
 */
public class Address {
	
	private String city;
	
	private String street;

	/**
	 * 
	 */
	public Address(final String city, final String street) {
		this.city = city;
		this.street = street;
	}

	/**
	 * @return the city
	 */
	public String getCity() {
		return city;
	}

	/**
	 * @param city the city to set
	 */
	public void setCity(final String city) {
		this.city = city;
	}

	/**
	 * @return the street
	 */
	public String getStreet() {
		return street;
	}

	/**
	 * @param street the street to set
	 */
	public void setStreet(final String street) {
		this.street = street;
	}

	@Override
	public boolean equals(final Object obj) {
		if (!(obj instanceof Address)) {
			return false;
		}
		Address adr = (Address) obj;
		return this.getCity().equals(adr.getCity()) && this.getStreet().equals(adr.getStreet());
	}
	
	@Override
	public int hashCode() {
		return city.hashCode(); 
	}
}
