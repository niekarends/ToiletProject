import { Component } from '@angular/core';

import { NavController, NavParams } from 'ionic-angular';

import { ItemDetailsPage } from '../item-details/item-details';

@Component({
	selector: 'page-hello-ionic',
	templateUrl: 'hello-ionic.html'
})
export class HelloIonicPage {
	icons: string[];
  items: Array<{title: string, icon: string}>;

  constructor(public navCtrl: NavController, public navParams: NavParams) {
    this.icons = ['flask', 'wifi', 'beer', 'football', 'basketball', 'paper-plane',
    'american-football', 'boat', 'bluetooth', 'build'];

    this.items = [];

    this.items.push({
    	title: 'Heren Toilet Links ',
        icon: 'checkmark-circle'
    })

    this.items.push({
    	title: 'Heren Toilet Rechts ',
        icon: 'checkmark-circle'
    })

    
  }

  itemTapped(event, item) {
    this.navCtrl.push(ItemDetailsPage, {
      item: item
    });
  }
}