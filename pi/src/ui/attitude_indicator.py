import pygame
import os

class AttitudeIndicator:
    def __init__(self, window_size, assets_path: str):
        self.window_size = window_size
        self.canvas = pygame.display.set_mode(window_size)

        self.ai = pygame.image.load(os.path.join(assets_path, "att.png"))
        self.ai_indicator_pitch = pygame.image.load(os.path.join(assets_path, "ai_indicator_pitch.png"))

    def __del__(self):
        pygame.quit()

    def update(self, pitch: int, roll: int):
        ai_crop = self.ai.subsurface(0, 360 - pitch * 4, self.ai.get_size()[0], self.ai.get_size()[1] - 720)
        ai_rotate = pygame.transform.rotate(ai_crop, roll)
        ai_indicator_pitch_rotate = pygame.transform.rotate(self.ai_indicator_pitch, roll)

        ai_rotate_calib = ai_rotate.subsurface(ai_rotate.get_size()[0] // 2 - self.window_size[0] // 2,
                                                ai_rotate.get_size()[1] // 2 - self.window_size[1] // 2,
                                                self.window_size[0],
                                                self.window_size[1])

        self.canvas.blit(ai_rotate_calib, (0, 0))
        self.canvas.blit(ai_indicator_pitch_rotate, (self.window_size[0] // 2 - ai_indicator_pitch_rotate.get_size()[0] // 2,
                                            self.window_size[1] // 2 - ai_indicator_pitch_rotate.get_size()[1] // 2))
        pygame.display.update()

    def quit(self):
        pygame.quit()