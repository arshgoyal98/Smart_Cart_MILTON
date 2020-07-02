package com.abhinav.lowesapp;

import android.database.Cursor;

public class GroceryItem {
	public long id;
	public String text;
//	public double price;
	public boolean checked;

	public GroceryItem(Cursor c) {
		id = c.getLong(c.getColumnIndex(GroceryProvider.KEY_ROWID));
		text = c.getString(c.getColumnIndex(GroceryProvider.KEY_TEXT));
		checked = (c.getInt(c.getColumnIndex(GroceryProvider.KEY_CHECKED)) == 1);
//		price = c.getDouble(c.getColumnIndex(GroceryProvider.KEY_TEXT));
	}
}
