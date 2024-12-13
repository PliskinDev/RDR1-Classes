#pragma once

#include <cstdint>
#include <new>

namespace rage
{
    class pgBase
    {
    public:
        virtual ~pgBase() = default;
        virtual bool MapContainsPointer(const void* ptr) const noexcept { return false; }
        virtual bool IsSafeToDelete() const noexcept { return true; }
        static void operator delete(void* ptr) noexcept { ::operator delete(ptr); }
        virtual void BeforeCopy() = 0;
        void SetPageMap(uint32_t* map) noexcept { m_pageMap = map; }
    private:
        static uint32_t sm_mapSize;
        uint32_t* m_pageMap;
    };

    class pgBaseAllocated : public pgBase
    {
    public:
        void* operator new(size_t size) 
        {
            return ::operator new(size);
        }

        void operator delete(void* ptr) noexcept {
            ::operator delete(ptr);
        }

        void* operator new[](size_t size) {
            return ::operator new[](size);
        }

        void operator delete[](void* ptr) noexcept {
            ::operator delete[](ptr);
        }

        virtual ~pgBaseAllocated() noexcept = default;
    };

    class pgBaseRefCounted
    {
    public:
        virtual ~pgBaseRefCounted() = default;
    };
    static_assert(sizeof(pgBaseRefCounted) == 0x8);
}