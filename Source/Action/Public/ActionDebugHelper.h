#pragma once

namespace Debug
{
	/**
	* @brief 在屏幕上打印调试消息并输出到日志
	 * 
	 * 该静态函数将消息显示在游戏屏幕上，同时记录到UE日志系统中。
	 * 如果GEngine指针无效，则不执行任何操作。
	 * 
	 * @param Msg 要显示的消息文本
	 * @param Color 消息显示的颜色，默认为随机颜色
	 * @param InKey 消息的唯一标识键，用于替换具有相同键的旧消息，默认为-1表示不替换
	 */
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValueToPrint, int32 InKey = -1,
	                  const FColor& Color = FColor::MakeRandomColor())
	{
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);

			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg)
		}
	}
}
