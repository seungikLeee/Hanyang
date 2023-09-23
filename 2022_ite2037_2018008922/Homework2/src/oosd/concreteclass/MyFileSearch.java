package oosd.concreteclass;

import oosd.abstractclass.FileSearch;
import oosd.abstractclass.SearchResult;

import java.io.File;

public class MyFileSearch extends FileSearch {
    MySearchResult result = new MySearchResult();
    @Override
    public SearchResult searchForFile(File root, String queryText, int max) {
        if(!root.isDirectory()) {}
        else {
            for (File folderItem:root.listFiles()) {
                // Recurse if it ’s a director
                if (folderItem.isDirectory()) {
                    if (folderItem.getName().contains(queryText)) {
                        result.addFile(folderItem);
                    }
                    searchForFile(folderItem, queryText, max);
                }
                else {
                    if (folderItem.getName().contains(queryText)){
                        result.addFile(folderItem);
                    }
                }
            }
        }
        return result;
    }
}