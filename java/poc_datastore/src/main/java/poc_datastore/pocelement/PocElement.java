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

import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * 
 * @author Gabriel Dimitriu
 *
 */
public class PocElement extends PocElementBase {

	@JsonProperty("poc_id")
	private int pocId;
	
	public PocElement() {
		
	}
	
	public PocElement(@JsonProperty("poc_id") final int id, @JsonProperty("poc_name") final String name, @JsonProperty("poc_value") final String value) {
		super(name, value);
		this.pocId = id;
	}

	/**
	 * @return the id
	 */
	public int getPocId() {
		return pocId;
	}
	/**
	 * @param id the id to set
	 */
	public void setPocId(int id) {
		this.pocId = id;
	}
	
	@Override
	public boolean equals(final Object obj) {
		if (!(obj instanceof PocElement)) {
			return false;
		}
		if (!super.equals(obj)) {
			return false;
		}
		if (((PocElement) obj).getPocId() == pocId) {
			return true;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		return this.getName().hashCode();
	}
}
