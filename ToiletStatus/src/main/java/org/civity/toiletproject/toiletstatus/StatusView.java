/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.civity.toiletproject.toiletstatus;

import java.util.ArrayList;
import java.util.List;
import javax.ejb.Singleton;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import org.primefaces.json.JSONArray;
import org.primefaces.json.JSONObject;

/**
 *
 * @author niekarends
 */
@Singleton
@ManagedBean(name = "StatusView", eager = true)
@ApplicationScoped
public class StatusView {

    private List<Toilet> toilets = new ArrayList<>();

    public StatusView() {
	System.out.println("Im initialized");
	updateToiletList();
    }

    private boolean toiletOccupied = false;

    public void updateToiletList() {
//	System.out.println("Updating Toilet list");
	Client client = ClientBuilder.newClient();
	String response = client.target("http://185.170.7.129:1026/v2/entities?type=toiletSensor").request().get(String.class);

	toilets.clear();
	JSONArray test = new JSONArray(response);

	for (int i = 0; i < test.length(); i++) {
	    Toilet t = new Toilet();
	    JSONObject tmp = test.getJSONObject(i);
	    t.setId(tmp.getString("id"));
	    t.setName(tmp.getJSONObject("name").getString("value"));
	    t.setStatus(tmp.getJSONObject("status").getString("value").equals("occupied"));
	    toilets.add(t);
	}
    }

    public List<Toilet> getToilets() {
	updateToiletList();
	return toilets;
    }

    public void setToilets(List<Toilet> toilets) {
	this.toilets = toilets;
    }
}
