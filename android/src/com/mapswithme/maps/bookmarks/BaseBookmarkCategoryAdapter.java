package com.mapswithme.maps.bookmarks;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;

import com.mapswithme.maps.bookmarks.data.BookmarkCategory;

import java.util.List;

public abstract class BaseBookmarkCategoryAdapter<V extends RecyclerView.ViewHolder>
    extends RecyclerView.Adapter<V>
{
  @NonNull
  private final Context mContext;
  @NonNull
  private List<BookmarkCategory> mItems;

  BaseBookmarkCategoryAdapter(@NonNull Context context, @NonNull List<BookmarkCategory> items)
  {
    mContext = context;
    mItems = items;
  }

  public void setItems(@NonNull List<BookmarkCategory> items)
  {
    mItems = items;
    notifyDataSetChanged();
  }

  @NonNull
  protected Context getContext()
  {
    return mContext;
  }

  @NonNull
  public List<BookmarkCategory> getBookmarkCategories()
  {
    return mItems;
  }

  @Override
  public int getItemCount()
  {
    return getBookmarkCategories().size();
  }

  @NonNull
  public BookmarkCategory getCategoryByPosition(int position)
  {
    List<BookmarkCategory> categories = getBookmarkCategories();
    if (position < 0 || position > categories.size() - 1)
      throw new ArrayIndexOutOfBoundsException(position);
    return categories.get(position);

  }
}
