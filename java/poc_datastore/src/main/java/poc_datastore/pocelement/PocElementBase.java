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
package poc_datastore.pocelement;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * @author Gabriel Dimitriu
 *
 */
public class PocElementBase {

	
	
	@JsonProperty("poc_name")
	private String name;
	
	@JsonProperty("poc_value")
	private String value;
	/**
	 * 
	 */
	public PocElementBase() {
		// TODO Auto-generated constructor stub
	}
	
	@JsonCreator
	public PocElementBase(@JsonProperty("poc_name") final String name, @JsonProperty("poc_value") final String value) {
		this.name = name;
		this.value = value;
	}
	
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
	/**
	 * @return the value
	 */
	public String getValue() {
		return value;
	}
	/**
	 * @param value the value to set
	 */
	public void setValue(String value) {
		this.value = value;
	}
	
	@Override
	public boolean equals(final Object obj) {
		if (!(obj instanceof PocElementBase)) {
			return false;
		}
		PocElementBase base = (PocElementBase) obj;
		if (base.getName().equals(this.getName()) && base.getValue().equals(this.getValue())) {
			return true;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		return this.getName().hashCode();
	}

}
