
// اضافه کردن فایل pch.h
#include "pch.h"
// اضافه کردن هدر فایل SFML برای گرافیک
#include <SFML/Graphics.hpp>
 // اضافه کردن هدر فایل iostream برای ورودی و خروجی استاندارد
#include <iostream>
// اضافه کردن هدر فایل random برای تولید اعداد تصادفی
#include <random>
// اضافه کردن هدر فایل deque برای استفاده از داده‌ساختار دوطرفه
#include <deque>
 // تعریف ثابت gridSize با مقدار 20
const int gridSize = 20;
// تعریف ثابت screenWidth با مقدار 800
const int screenWidth = 800;
// تعریف ثابت screenHeight با مقدار 600
const int screenHeight = 600;
// تعریف کلاس Game
class Game {

public:
    // تعریف کانستراکتور کلاس Game
    Game();
    // تعریف تابع run برای اجرای بازی
    void run();

private:
    // تعریف تابع processEvents برای پردازش رویدادها
    void processEvents();
    // تعریف تابع update برای بروزرسانی بازی
    void update();
    // تعریف تابع render برای رسم بازی
    void render();
    // تعریف تابع handlePlayerInput برای پردازش ورودی کاربر
    void handlePlayerInput(sf::Keyboard::Key key);
    // تعریف تابع spawnMushroom برای ایجاد قارچ جدید
    void spawnMushroom();
    // تعریف تابع checkCollision برای بررسی تصادم با مار
    bool checkCollision(sf::Vector2f pos);
    // تعریف پنجره ی بازی به عنوان عضو داده‌ی کلاس
    sf::RenderWindow mWindow;
    // تعریف مار به عنوان شکل مستطیل در SFML
    sf::RectangleShape mSnake;
    // تعریف داده‌ساختار دوطرفه برای محورهای مار
    std::deque<sf::Vector2f> mSnakeSegments;
    // تعریف قارچ به عنوان شکل دایره در SFML
    sf::CircleShape mMushroom;
    // تعریف جهت حرکت مار
    sf::Vector2f mSnakeDirection;
    // تعریف موقعیت مار
    sf::Vector2f mSnakePosition;
    // تعریف موقعیت قارچ
    sf::Vector2f mMushroomPosition;
    // متغیر جهت نگهداری تعداد لول‌ها
    int mLevel = 0;
    // متغیر جهت نگهداری امتیاز بازیکن
    int mScore = 0;
};
     // تعریف کانستراکتور کلاس Game
Game::Game() : mWindow(sf::VideoMode(screenWidth, screenHeight), "Snake Game")
{   // تنظیم ابعاد مستطیل مار
    mSnake.setSize(sf::Vector2f(gridSize, gridSize));
    // تنظیم رنگ مستطیل مار
    mSnake.setFillColor(sf::Color::Green);
    // تنظیم موقعیت اولیه مار
    mSnakePosition = sf::Vector2f(screenWidth / 2, screenHeight / 2);
    // تنظیم موقعیت مستطیل مار
    mSnake.setPosition(mSnakePosition);
    // اضافه کردن موقعیت اولیه مار به داده‌ساختار دوطرفه
    mSnakeSegments.push_front(mSnakePosition);
    // تنظیم جهت حرکت اولیه مار
    mSnakeDirection = sf::Vector2f(gridSize, 0);
    // تنظیم شعاع دایره قارچ
    mMushroom.setRadius(gridSize / 2);
    // تنظیم رنگ دایره قارچ
    mMushroom.setFillColor(sf::Color::Red);
    // ایجاد یک رشته تصادفی
    std::random_device rd;
    // ایجاد موتور تصادفی با رشته تصادفی
    std::default_random_engine engine(rd());
    // توزیع یکنواخت برای اعداد در محور x
    std::uniform_int_distribution<int> xDistribution(0, screenWidth / gridSize - 1);
    // توزیع یکنواخت برای اعداد در محور y
    std::uniform_int_distribution<int> yDistribution(0, screenHeight / gridSize - 1);
    // تولید موقعیت تصادفی قارچ در محور x
    mMushroomPosition.x = xDistribution(engine) * gridSize;
    // تولید موقعیت تصادفی قارچ در محور y
    mMushroomPosition.y = yDistribution(engine) * gridSize;
    // تنظیم موقعیت دایره قارچ
    mMushroom.setPosition(mMushroomPosition);
}
// تعریف تابع run که بازی را اجرا می‌کند
void Game::run()
{
    // تکرار تا زمانی که پنجره باز است
    while (mWindow.isOpen()) {
        // پردازش رویدادها
        processEvents();
        // بروزرسانی بازی
        update();
        // رسم بازی
        render();
    }
}
// تعریف تابع processEvents برای پردازش رویدادها
void Game::processEvents()
{
    sf::Event event;
////////////////////////////////////////////////////////////////////////////////////////////////////////
   /*
// تعریف عکس خاک به عنوان پس‌زمینه
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("path/to/background.png"); // مسیر تصویر پس‌زمینه را وارد کنید

    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    */
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // دریافت رویدادها تا زمانی که رویدادی وجود داشته باشد
    while (mWindow.pollEvent(event)) {
        // اگر رویداد بستن پنجره رخ داد
        if (event.type == sf::Event::Closed)
        // بستن پنجره
            mWindow.close();
        // اگر رویداد کلید فشرده شده رخ داد
        else if (event.type == sf::Event::KeyPressed)
            // پردازش ورودی کاربر
            handlePlayerInput(event.key.code);
    }
}
// تعریف تابع update برای بروزرسانی بازی
void Game::update()
{   // توقف بازی به مدت 200 میلی‌ثانیه
    sf::sleep(sf::milliseconds(200));
    // محاسبه موقعیت جدید مار
    sf::Vector2f newSnakePosition = mSnakePosition + mSnakeDirection;
    if (newSnakePosition.x < 0 || newSnakePosition.x >= screenWidth ||
        newSnakePosition.y < 0 || newSnakePosition.y >= screenHeight ||
        // اگر مار با دیوار برخورد کند یا با خودش تصادف کند
        checkCollision(newSnakePosition)) {
        // چاپ پیام باخت در خروجی استاندارد
        std::cout << "Game Over!" << std::endl;
        // بستن پنجره
        mWindow.close();
        return;
    }
    // بروزرسانی موقعیت مار
    mSnakePosition = newSnakePosition;
    // تنظیم موقعیت مستطیل مار
    mSnake.setPosition(mSnakePosition);
    // اضافه کردن موقعیت جدید مار به داده‌ساختار دوطرفه
    mSnakeSegments.push_front(mSnakePosition);
    // اگر مار با قارچ برخورد کند
    if (mSnakePosition == mMushroomPosition) {
        // اضافه کردن موقعیت جدید مار به داده‌ساختار دوطرفه
        mSnakeSegments.push_front(mSnakePosition);
        // ایجاد قارچ جدید
        spawnMushroom();
    }
    else {
        // حذف موقعیت آخر دنباله مار
        mSnakeSegments.pop_back();
    }
}
// تعریف تابع render برای رسم بازی
void Game::render()
{
    ////////////////////////////////////////////////////////////////////////////////
    /*
    // رسم عکس پس‌زمینه
    mWindow.draw(background);
    */
    /////////////////////////////////////////////////////////////////////////////////
    // پاک کردن پنجره با رنگ قهوه‌ای
    mWindow.clear(sf::Color(139, 69, 19)); // قهوه‌ای
    // رسم مستطیل مار
    mWindow.draw(mMushroom);
    // برای هر عنصر در داده‌ساختار دوطرفه
    for (const sf::Vector2f& segment : mSnakeSegments) {
        // ایجاد شکل مستطیل با ابعاد مشخص شده
        mSnake.setSize(sf::Vector2f(gridSize, gridSize));
        // تنظیم موقعیت مستطیل
        mSnake.setPosition(segment);
        // رسم دایره قارچ
        mWindow.draw(mSnake);
//////////////////////////////////////////////////////////////
        // رسم مستطیل
        //  mWindow.draw(segmentShape);  
        // تنظیم رنگ مستطیل
        // segmentShape.setFillColor(sf::Color::Green); 
//////////////////////////////////////////////////////////////
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    // نمایش تعداد لول‌ها و امتیاز بازیکن
    sf::Font font;
    font.loadFromFile("path/to/font.ttf"); // مسیر فونت را وارد کنید

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level: " + std::to_string(mLevel));
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10, 10);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(mScore));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 40);

    mWindow.draw(levelText);
    mWindow.draw(scoreText);
    */
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // نمایش پنجره
    mWindow.display();
}
// تعریف تابع handlePlayerInput برای پردازش ورودی کاربر
void Game::handlePlayerInput(sf::Keyboard::Key key)
{
    // اگر کلید فشرده شده بالا بود و مار به سمت پایین نبود
    if (key == sf::Keyboard::Up && mSnakeDirection.y != gridSize)
        // تنظیم جهت حرکت به بالا
        mSnakeDirection = sf::Vector2f(0, -gridSize);
    // اگر کلید فشرده شده پایین بود و مار به سمت بالا نبود
    else if (key == sf::Keyboard::Down && mSnakeDirection.y != -gridSize)
        // تنظیم جهت حرکت به پایین
        mSnakeDirection = sf::Vector2f(0, gridSize);
    // اگر کلید فشرده شده چپ بود و مار به سمت راست نبود
    else if (key == sf::Keyboard::Left && mSnakeDirection.x != gridSize)
        // تنظیم جهت حرکت به چپ
        mSnakeDirection = sf::Vector2f(-gridSize, 0);
    // اگر کلید فشرده شده راست بود و مار به سمت چپ نبود
    else if (key == sf::Keyboard::Right && mSnakeDirection.x != -gridSize)
        // تنظیم جهت حرکت به راست
        mSnakeDirection = sf::Vector2f(gridSize, 0);
}
// تعریف تابع spawnMushroom برای ایجاد قارچ جدید
void Game::spawnMushroom()
{
    // ایجاد یک رشته تصادفی
    std::random_device rd;
    // ایجاد موتور تصادفی با رشته تصادفی
    std::default_random_engine engine(rd());
    // توزیع یکنواخت برای اعداد در محور x
    std::uniform_int_distribution<int> xDistribution(0, screenWidth / gridSize - 1);
    // توزیع یکنواخت برای اعداد در محور y
    std::uniform_int_distribution<int> yDistribution(0, screenHeight / gridSize - 1);
    // متغیری برای بررسی صحت موقعیت قارچ
    bool validPosition = false;
    // متغیری برای نگهداری موقعیت جدید قارچ
    sf::Vector2f newPosition;
    // حلقه‌ای برای تولید موقعیت تصادفی تا زمانی که موقعیت معتبر باشد
    while (!validPosition) {
        // تولید موقعیت تصادفی قارچ در محور x
        newPosition.x = xDistribution(engine) * gridSize;
        // تولید موقعیت تصادفی قارچ در محور y
        newPosition.y = yDistribution(engine) * gridSize;
        // بررسی برخورد قارچ با سایر اشیاء در بازی
        if (!checkCollision(newPosition))
            // موقعیت معتبر است اگر برخوردی رخ ندهد
            validPosition = true; 
    }

    // ذخیره کردن موقعیت جدید قارچ
    mMushroomPosition = newPosition;
//////////////////////////////////////////////////////////////////////////////////////
     /*
    // افزایش تعداد لول‌ها
    mLevel++;
    // افزایش امتیاز با توجه به تعداد لول‌ها
    mScore += 10 * mLevel;
    */
///////////////////////////////////////////////////////////////////////////////////////
    // تنظیم موقعیت دایره قارچ
    mMushroom.setPosition(mMushroomPosition);
}
// تعریف تابع checkCollision برای بررسی تصادف مار با خودش یا دیوار
bool Game::checkCollision(sf::Vector2f pos)
{ // برای هر عنصر در داده‌ساختار دوطرفه
    for (const auto& segment : mSnakeSegments) {
        // اگر عنصر با موقعیت داده شده برابر بود
        if (segment == pos)
            // برگرداندن مقدار درست
            return true;
    }
    // برگرداندن مقدار غلط
    return false;
}
int main() //نفطه شروع اجرای  برنامه
{
    Game game; // برای اجرای بازی
    game.run();//اجرای بازی تا زمانی که پنجره بازی باز است به طور مداوم ورودی هارا پردازش کرده وضعیت بازی را به روز رسانی می کند و صفحه بازی را رسم می کند
    return 0;//بازگشت به مقدار صفر
}