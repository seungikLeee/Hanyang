package com.needimplementation;

import java.util.ArrayList;

// TODO Implement this class, do not modify the existing code but only add from it
public class Kitchen {

  private ArrayList<Thread> aList = new ArrayList<>();
  private ArrayList<Order> orderList = new ArrayList<>();

  public void cook(Order o) {
    orderList.add(o);
    Thread t = new Thread(o);
    t.start();
    aList.add(t);
  }

  public boolean isAllOrderFinished() {
    for(Thread th: aList){
      if(th.isAlive()) {
        return false;
      }
    }
    return true;
  }

  public Order[] getAllUnfinishedOrders() {
    int count = 0;
    for(Thread th: aList){
      if(th.isAlive()) {
        count++;
      }
    }

    Order[] order = new Order[count];
    int j=0;
    for(int i=0; i< aList.size(); i++){
      if(aList.get(i).isAlive()) {
        order[j] = orderList.get(i);
        j++;
      }
    }

    return order;
  }
}
