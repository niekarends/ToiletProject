import { Component } from '@angular/core';

import { NavController, NavParams } from 'ionic-angular';

import { ItemDetailsPage } from '../item-details/item-details';

import {HttpClient} from '@angular/common/http';

import 'rxjs/add/operator/map';

@Component({
	selector: 'page-hello-ionic',
	templateUrl: 'hello-ionic.html'
})
export class HelloIonicPage {

  // items: Array<{name: string, status: string}>;
  items:any;

  constructor(public navCtrl: NavController, public navParams: NavParams,private http: HttpClient) {
    this.getToiletList() ;
    

    // this.items.push({
    // 	  name: 'Heren Toilet Links ',
    //     status: 'free'
    // })

    // this.items.push({
    // 	  name: 'Heren Toilet Rechts ',
    //     status: 'occupied'
    // })

    
  }

  itemTapped(event, item) {
    this.navCtrl.push(ItemDetailsPage, {
      item: item
    });
  }

  getToiletList() {
    this.items = [];
    this.http.get('/entities?type=toiletSensor').subscribe(data => this.items = data);
    console.log('Getting list of toilets');
  }

  doRefresh() {
    console.log('Begin async operation');
    this.getToiletList() ;
    setTimeout(() => {
      console.log('Async operation has ended');
    }, 0);
  }
}