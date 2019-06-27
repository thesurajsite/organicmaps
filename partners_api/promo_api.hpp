#pragma once

#include "partners_api/utm.hpp"

#include "metrics/eye.hpp"

#include "platform/safe_callback.hpp"

#include "geometry/point2d.hpp"

#include <memory>
#include <string>
#include <vector>

#include "private.h"

namespace promo
{
struct Author
{
  std::string m_id;
  std::string m_name;
};
struct LuxCategory
{
  std::string m_name;
  std::string m_color;
};

struct CityGallery
{
  struct Item
  {
    std::string m_name;
    std::string m_url;
    std::string m_imageUrl;
    std::string m_access;
    std::string m_tier;
    Author m_author;
    LuxCategory m_luxCategory;
  };

  std::string m_moreUrl;
  std::vector<Item> m_items;
};

struct AfterBooking
{
  std::string m_promoUrl;
  std::string m_pictureUrl;
};

class WebApi
{
public:
  static bool GetCityGalleryById(std::string const & baseUrl, std::string const & id,
                                 std::string const & lang, std::string & result);
};

using CityGalleryCallback = platform::SafeCallback<void(CityGallery const & gallery)>;
using OnError = platform::SafeCallback<void()>;

class Api : public eye::Subscriber
{
public:
  class Delegate
  {
  public:
    virtual ~Delegate() = default;

    virtual std::string GetCityId(m2::PointD const & point) = 0;
  };


  Api(std::string const & baseUrl = BOOKMARKS_CATALOG_FRONT_URL,
      std::string const & basePicturesUrl = PICTURES_URL);

  void SetDelegate(std::unique_ptr<Delegate> delegate);
  void OnEnterForeground();
  bool NeedToShowAfterBooking() const;
  AfterBooking GetAfterBooking(std::string const & lang) const;
  std::string GetPromoLinkForDownloader(std::string const & id, std::string const & lang) const;
  std::string GetMoreUrl(std::string const & id) const;
  void GetCityGallery(m2::PointD const & point, std::string const & lang, UTM utm,
                      CityGalleryCallback const & onSuccess, OnError const & onError) const;

  // eye::Subscriber overrides:
  void OnMapObjectEvent(eye::MapObject const & poi) override;

private:
  std::unique_ptr<Delegate> m_delegate;

  std::string const m_baseUrl;
  std::string const m_basePicturesUrl;
  std::string m_bookingPromoAwaitingForId;
};
}  // namespace promo
