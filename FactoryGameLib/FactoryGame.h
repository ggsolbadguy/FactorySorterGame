/**
 * @file FactoryGame.h
 * @author Tyler Stefan
 *
 * main class for the game
 */
 
#ifndef FACTORYGAME_H
#define FACTORYGAME_H
#include <random>

#include "Bucket.h"
#include "Item.h"
#include "OutputMachine.h"

/**
 * main class for the game
 */
class FactoryGame {
private:

    /// the list of items within the game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Directory containing the system images
    std::wstring mImagesDirectory;
    /// Directory containing the level files
    std::wstring mLevelsDirectory;
    /// Random number generator
    std::mt19937 mRandom;

    /// time since the last part was spawned
    double mTimeSinceSpawned = 0.0;
    /// part spawn generation interval
    double mPartGenerationInterval = 0.0;
    /// image scalar for scaling up pixel art
    double mImageScale = 4.0;

    /// the bucket in this factory
    std::shared_ptr<Bucket> mBucket;
    /// the bucket in this factory
    std::shared_ptr<OutputMachine> mOutputMachine;

    /// the loaded in movement speed of parts
    double mPartSpeed = 0.0;
    /// class for representing the game state
    enum class GameState
    {
        Playing,
        Won,
        Lost,
        Instructions
    };
    /// represents the game state
    GameState mGameState = GameState::Instructions;
    /// current level number
    int mCurrentLevel = 1;

public:
    FactoryGame();
    void SetImagesDirectory(const std::wstring& dir);
    void SetLevelsDirectory(const std::wstring& dir);
    void Update(double elapsed);
    /**
     * get the images directory of this game
     * @return images directory
     */
    std::wstring GetImagesDirectory() const { return mImagesDirectory; }
    /**
     * get the image scale of this game
     * @return image scale
     */
    double GetImageScale() const { return mImageScale; }
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc);
    void Load(const wxString& filename);
    void XmlItem(wxXmlNode* node);
    void Clear();
    void HandleInput(wxKeyEvent& event);
    void CreatePart();
    /**
     * set the game to lost state
     */
    void SetGameOver() { mGameState = GameState::Lost; }
    /**
     * returns true if the user has lost the game
     * @return true if the player lost
     */
    bool IsGameOver() { return mGameState == GameState::Lost; }

    /**
     * set the game won status
     */
    void SetGameWon() {mGameState = GameState::Won; }
    /**
     * checks if the player has won
     * @return true if the player won
     */
    bool IsGameWon() { return mGameState == GameState::Won; }

    /**
     * set the game state to playing
     */
    void SetPlaying() { mGameState = GameState::Playing; }
    /**
     * checks if the player is playing
     * @return true if the player is playing
     */
    bool IsPlaying() { return mGameState == GameState::Playing; }

    /**
     * set the game state to playing
     */
    void SetGameInstructions() { mGameState = GameState::Instructions; }
    /**
     * checks if the instructions are up
     * @return true if instructions are active
     */
    bool IsInstructions() { return mGameState == GameState::Instructions; }

    /**
     * get the output machine of this game
     * @return mOutputMachine
     */
    std::shared_ptr<OutputMachine> GetOutputMachine() const { return mOutputMachine; }
    /**
     * get the bucket of this game
     * @return mBucket
     */
    std::shared_ptr<Bucket> GetBucket() const { return mBucket; }
    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * set the current level number
     * @param levelNumber level number to set
     */
    void SetLevelNumber(int levelNumber) { mCurrentLevel = levelNumber; }
    /**
     * get the current level number
     * @return mCurrentLevel
     */
    int GetLevelNumber() const { return mCurrentLevel; }

};



#endif //FACTORYGAME_H
