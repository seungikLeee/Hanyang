package com.needimplementation;

import com.Main;

import java.util.Scanner;

// TODO Implement this class, do not modify the existing code but only add from it
public class Order implements Runnable {

  private String name;
  private String[] menu;

  public static Order[] loadOrder(Scanner scanner) {
    int num = scanner.nextInt();

    scanner.nextLine();
    Order[] order = new Order[num];

    for(int j=0; j<num; j++){
      order[j] = new Order();
      order[j].name = scanner.nextLine();
      int mNum = scanner.nextInt();
      scanner.nextLine();
      for(int i=0; i<mNum; i++){
        order[j].menu = new String[mNum];
        order[j].menu[i] = scanner.nextLine();
      }
    }
    return order;
  }

  public String getName(){
    return this.name;
  }

  public String[] getMenu(){
    return this.menu;
  }

  @Override
  public String toString(){
    return this.getName();
  }

  @Override
  public void run() {
    try {
      for(String Menu : menu){
        cook(Menu);
      }
      Main.println(">>Order from [" + this + "] finished");
    } catch (InterruptedException ignored) {
      // Should never ever happen if program is implemented as requested
    }
  }

  private void cook(String dish) throws InterruptedException {
    switch (dish) {
      case "egg":
        Thread.sleep(50);
        break;
      case "ramen":
        Thread.sleep(100);
        break;
      case "friedrice":
        Thread.sleep(150);
        break;
      case "ovenroast":
        Thread.sleep(200);
        break;
      case "bibimmyon":
        Thread.sleep(250);
        break;
      default:
        break;
    }
  }
}
