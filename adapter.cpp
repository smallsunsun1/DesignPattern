//
// Created by 孙嘉禾 on 2020/1/19.
//

#include <iostream>
#include <string>
#include <memory>

class MediaPlayer {
 public:
  virtual void Play(const std::string& audio_type, const std::string& filename) = 0;
  virtual ~MediaPlayer() = default;
};

class AdvancedMediaPlayer {
 public:
  virtual void PlayVlc(const std::string& fileName) = 0;
  virtual void PlayMp4(const std::string& fileName) = 0;
  virtual ~AdvancedMediaPlayer() = default;
};

class VlcPlayer: public AdvancedMediaPlayer {
 public:
  void PlayVlc(const std::string &fileName) override {
    std::cout << "Playing vlc file. Name: " + fileName;
  }
  void PlayMp4(const std::string &fileName) override {}
};

class Mp4Player: public AdvancedMediaPlayer {
 public:
  void PlayVlc(const std::string &fileName) override {

  }
  void PlayMp4(const std::string &fileName) override {
    std::cout << "Playing mp4 file. Name: " + fileName;
  }
};

class MediaAdapter: public MediaPlayer {
 public:
  MediaAdapter() = default;
  explicit MediaAdapter(const std::string& audio_type) {
    if (audio_type == "vlc") {
      advanced_media_player_ = std::make_unique<VlcPlayer>();
    } else if (audio_type == "mp4") {
      advanced_media_player_ = std::make_unique<Mp4Player>();
    }
  }
  void Play(const std::string &audio_type, const std::string &filename) override {
    if (audio_type == "vlc")
      advanced_media_player_->PlayVlc(filename);
    else if (audio_type == "mp4")
    advanced_media_player_->PlayMp4(filename);
  }
 private:
  std::unique_ptr<AdvancedMediaPlayer> advanced_media_player_;
};

class AudioPlayer: public MediaPlayer {
 public:
  explicit AudioPlayer() = default;
  void Play(const std::string &audio_type, const std::string &filename) override {
    if (audio_type == "mp3") {
      std::cout << "Playing mp3 file. Name: " + filename;
    } else if (audio_type == "vlc") {
      media_adapter_ = MediaAdapter(audio_type);
      media_adapter_.Play(audio_type, filename);
    } else {
      std::cout << "Invalid media. " + audio_type + " format not supported";
    }
  }
 private:
  MediaAdapter media_adapter_;
};

int main() {
  AudioPlayer* player = new AudioPlayer();
  player->Play("mp3", "aa");
  player->Play("mp4", "bb");
  player->Play("vlc", "cc");
  delete player;
  return 0;
}

