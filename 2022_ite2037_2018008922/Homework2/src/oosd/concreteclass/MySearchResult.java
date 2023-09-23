package oosd.concreteclass;

import oosd.abstractclass.SearchResult;

import java.io.File;

public class MySearchResult extends SearchResult {
    public MySearchResult(){
        this.files = new File[5];
        this.size = 0;
        this.max=5;
    }

    @Override
    public int getSize() {
        return this.size;
    }

    @Override
    public File[] getFiles() {
        return this.files;
    }

    @Override
    public boolean isMax() {
        if(this.size == this.max) return true;
        else return  false;
    }

    @Override
    public void addFile(File file) {
        if (isMax()) {
        } else {
            this.files[this.size] = file;
            this.size++;
        }
    }

    @Override
    public SearchResult copy() {
        MySearchResult sr = new MySearchResult();
        for (int i = 0; i < 5; i++) {
            File copyfile = new File("C:\\");
            copyfile = this.files[i];
            sr.getFiles()[i] = copyfile;
        }
        return sr;
    }
}