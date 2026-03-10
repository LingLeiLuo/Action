--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type AN_SendGameplayEventToOwner_C
local M = UnLua.Class()

function M:Received_Notify(MeshComp, Animation)
    local payload = UE.FGameplayEventData()

    --我草了，蓝图属性默认带空格直接调不出来，还得self["  "]的形式
    UE.UAbilitySystemBlueprintLibrary.SendGameplayEventToActor(
            MeshComp:GetOwner(), self["Event Tag"], payload)

    print("Received_Notify: " .. tostring(self["Event Tag"]))

    return true
end

return M